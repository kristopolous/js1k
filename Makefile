sdl: animate.c
	gcc32 -O6 -o sdl -Wall -fpeephole -fomit-frame-pointer -fthread-jumps -fexpensive-optimizations -ffunction-cse -fcaller-saves animate.c -L/usr/local/lib -I/usr/local/include/SDL11 -lSDL-1.1 -pthread
debug: SDLtest.c
	gcc32 -gstabs+ -o sdl -Wall SDLtest.c -L/usr/local/lib -I/usr/local/include/SDL11 -lSDL-1.1 -pthread
tiff: tifftest.c
	gcc32 -o tiff -fpeephole  -fomit-frame-pointer -fthread-jumps   -fexpensive-optimizations   -ffunction-cse    -fcaller-saves -Wall -O3 -L /usr/local/lib -lnetpbm tifftest.c 
