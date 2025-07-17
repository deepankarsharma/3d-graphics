build:
	gcc -O0 -ggdb3 -Wall -std=c99 ./src/*.c -lSDL2 -o renderer 

run:
	./renderer

clean:
	rm renderer
