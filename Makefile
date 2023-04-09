CC=gcc
CFLAGS=-Wall
BUILDIR=build
SRCDIR=src

all: $(BUILDIR) | main 

$(BUILDIR):
	mkdir $(BUILDIR)

build/ngrad.o: $(SRCDIR)/ngrad.c $(SRCDIR)/ngrad.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/ngrad.c -o $(BUILDIR)/ngrad.o
	
main: $(SRCDIR)/main.c $(BUILDIR)/ngrad.o 
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -rf $(BUILDIR)
	rm $(SRCDIR)/main.o
	rm main
