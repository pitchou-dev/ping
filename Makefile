all:
	gcc -I src/include -L src/lib -o ping ping.c -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf