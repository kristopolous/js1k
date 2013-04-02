<img src=http://i.imgur.com/HpAXScw.jpg>

*This is my contribution for js1k for spring/2013.*

It's based on some code I wrote in 2002. That's why all the C stuff is here.

Here's what the HTML looks like:

<img width=200 height=200 src=http://i.imgur.com/VRsh9vv.gif>

You can see it [here](http://qaa.ath.cx/shim1.html) hosted by me

And, also, [on the js1k.com site](http://js1k.com/2013-spring/demo/1534).

I wrote this explanation for someone on [reddit](http://www.reddit.com/r/javascript/comments/1beq57/js1k_demo_an_animation_of_an_equation_system_i/c96oex2)

<blockquote>
well you are dealing with pixels first.  So you have a viewport, that's how many pixels you are seeing.  In this case I am using 768x768 (that's the first variable S=768).  Then I get a blank "image" which will be my canvas. I assign color values to that array, and then I "putImageData" back on the canvas.

For this application I'm using cartesian coordinates.  I decide on my region to view, this is like on the graphing calculators

you think you want to view say, between -10, -10 on the X scale and -10 and 10 on the Y scale.

This means that if you want to graph a line, say, y = 3x then you map each one of those points back to the pixel equivalency with a little division.

There's algorithms for drawing continuous lines efficiently well documented on wikipedia.


So for this one what I did is that I have a system of 3 equations:


      A = (A - C) / (-A + mul2 * B + C);
      B = (A - C) / (B - C + A);
      C = (A - C) / (mul * A - B + C);

And I iterate twice; once by mutating the initialization vector, [A,B,C] and another time by cycling the equation.

Then I take the [A,B] points and map them to a plane. I use the C value as the blue in the RGB color.  The range that I'm using is [-max, max], [-max, max] which means that 0,0 will always be in the center, the graph will always be proportional, and I can express the range in a single value.

For the purpose of the demo I oscillate this at   

    max = (Math.sin(3 + i2) + 1) * 4;

You can see things zoom out in the demo.  After about 45 or so seconds in when you see just blue dots vertically and horizontally, shortly after that you can tell that I'm zooming out.

There's also rotation in it - which is intentionally done slightly incorrectly.

Standard rotation about an angle, i2, of points, A, and B are as follows:

     ra = A * Math.cos(i2) - B * Math.sin(i2);
     rb = A * Math.sin(i2) + B * Math.cos(i2);

But I made things a bit less boring

     ra = A * Math.cos(i2) - B * Math.sin(i2);
     rb = A * Math.sin(C) + B * Math.cos(i2);

By adding our under-utilized C variable (which is just the blue channel) as part of the transformation. Therein, even when the map is at a stability point (see below); it still appears to be moving around.

If you take out all these things you get this: http://qaa.ath.cx/shim-boring.html
The multipliers are oscillated by trig functions between 0 and 8.  They are what "animate" it.  Without that oscillation it would be a single generation, like this: http://i.imgur.com/HpAXScw.jpg

AFAIK, this type of math isn't as well understood as say, 3d projection on a 2d plane (standard 3d stuff). So optimizations that can make things faster at least aren't known by me. So that's why in the js1k demo, the frames are partially rendered.  The image above was written in C and took about 20 minutes to generate on a modern i7 processor.

In the github repository you can find this file: https://github.com/kristopolous/js1k/blob/master/html/shim.html which isn't as cryptically compressed as the one submitted for the contest.  It's still not well done however as I was essentially just hacking.
</blockquote>

<img src=http://i.imgur.com/sQaMIAm.jpg>
