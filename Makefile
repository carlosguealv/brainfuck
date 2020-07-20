all: clean build

clean:
	rm -f brainfuck

build:
	gcc -o brainfuck brainfuck.c
