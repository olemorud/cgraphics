
all:
	mkdir -p bin
	cc graphics.c -o bin/graphics -lm -O3

clean:
	rm -rf bin/

debug:
	mkdir -p bin
	cc graphics.c -o bin/graphics -lm -g3
