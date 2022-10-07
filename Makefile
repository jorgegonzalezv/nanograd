CC=gcc
CFLAGS=-Wall

all: main

build/basic.o: libs/basic/basic.c libs/basic/basic.h
	$(CC) $(CFLAGS) -c libs/basic/basic.c -o build/basic.o

build/nn.o: libs/nn.c libs/nn.h
	$(CC) $(CFLAGS) -c libs/nn.c -o build/nn.o
	
main: src/main.c build/nn.o 
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -rf build/*.o
	rm src/main.o
	rm main
