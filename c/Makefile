sdl: modifiable.c
	gcc -O6 -o sdl -Wall -fpeephole -fomit-frame-pointer -fthread-jumps -fexpensive-optimizations -ffunction-cse -fcaller-saves modifiable.c -L/usr/local/lib `pkg-config --cflags sdl` `pkg-config --libs sdl` -pthread
debug: SDLtest.c
	gcc -gstabs+ -o sdl -Wall SDLtest.c -L/usr/local/lib -I/usr/local/include/SDL11 -lSDL-1.1 -pthread
tiff: tifftest.c
	gcc -o tiff -fpeephole  -fomit-frame-pointer -fthread-jumps   -fexpensive-optimizations   -ffunction-cse    -fcaller-saves -Wall -O3 -L /usr/local/lib tifftest.c -lppm
ex2: example2.c
	gcc -o ex2 -fpeephole  -fomit-frame-pointer -fthread-jumps   -fexpensive-optimizations   -ffunction-cse    -fcaller-saves -Wall -O3 -L /usr/local/lib example2.c -lppm
