# Compiling

This is assuming that you are on ubuntu linux.

First make sure that you have build-essential installed. This will allow you to compile C programs.

Then there is an interactive version and a version that outputs PNM formatted images.

You'll need to install SDL for the interactive version.

    $ sudo apt-get install libsdl1.2-dev
    $ make
    $ ./sdl height width cycles

Apparently this old code will core-dump if it doesn't have the right number of args.


## SDL code

So try this

    $ ./sdl 800 600 10000

Now you'll get a window like this:

<img src=http://i.imgur.com/ydcPVHQ.png>

Looking at the source, apparently I had this interface:

 * Right click = zoom in
 * Middle click (left + right) = zoom out
 * Left click = center (pan)
 * j/k h/l o/n = color cycling
 * space bar = quit

This was originally written for a NetBSD laptop with a 90Mhz Pentium 1 and I think 16MB of RAM. 

I'm typing this on an i5-3210M with 16GB of RAM. My how times have changed.

## Static code

The static code, which is used to create the really nice screen shots is intensely poorly named tifftest.c

### Compiling

You need libnetpbm10-dev

    $ sudo apt-get install libnetpbm9-dev libnetpbm9

Yes I said **NINE**. Not 10.

After you are done you may be tempted to do this

    $ ./tiff

But that would be wrong, see.

Try this

    $ ./tiff | display

And now you get an error screen

<img src=http://i.imgur.com/7BhFrJs.png>

Because you haven't provided a ridiculous amount of undocumented arguments.

Looking at the source it looks like it's

    $ ./tiff height width cycles x-min y-min x-max y-max "c-m" "bri"

Where "c_m" appears to be the amount of blue and "bri" appears to be the amount of red.

Let's try something silly:

    $ ./tiff 300 300 100 -10 -10 10 10 10 10 | display -
<img src=http://i.imgur.com/YMcpgoE.png>

That works. Great.  Increase the cycles, change the color around, and zoom in:

    $ ./tiff 300 300 100000 -2 -2 2 2 100 30 | display -

<img src=http://i.imgur.com/w3gDSeb.png>

Let's go into the code and change the algorithm a bit. We are going to hijack the system of equations from "shim-new1.html"

    13   #define EQ1     a=(a-c)/(a*3.52-b);
    14   #define EQ2     b=(a-c)/(b-c);
    15   #define EQ3     c=(a-b)/(b+c);

    $ make tiff
    gcc -o tiff -fpeephole  -fomit-frame-pointer -fthread-jumps   -fexpensive-optimizations   -ffunction-cse    -fcaller-saves -Wall -O3 -L /usr/local/lib tifftest.c -lppm
    $ ./tiff 300 300 100000 -3 -3 3 3 10 5 | display -

<img src=http://i.imgur.com/bHdWTxj.png>

Wonderful. This is example1.c

## On to animation!

So the quickest way I can think of doing the equivalent of the html is to add another argument and make it scriptable.

Changing those lines again

    13   #define EQ1     a=(a-c)/(a*mul-b);
    14   #define EQ2     b=(a-c)/(b-c);
    15   #define EQ3     c=(a-b)/(b+c)

and a few other things, I get example2.c. Now using seq and xargs I can do the following:

    $ seq 1.85 0.003 7 | xargs -P 4 -n 1 ./animate_hack.sh 

Hah, that's something I'd never dream of doing on my pentium 90.

Well this took some serious time (about 28 hours over three machines). 

This left me with 8.7GB of PNGs.  Stitching them together like so:

    ffmpeg -y -f image2 -r 30 -i %05d.png -pix_fmt yuvj420p -sameq out.mkv

Generates a 2.2GB video that lasts 71 seconds.

I tried a number of things to get this down and finally did

    ffmpeg -i  out.mkv  -an -vcodec libx264 -preset veryslow -threads 2 -crf 30 -tune grain -y video.mp4

That brought it down to 140MB.  [here it is on youtube](http://youtu.be/bi0_wHlhZw0).
