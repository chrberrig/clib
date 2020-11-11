all: chbibkey

chbibkey: chbibkey.o
	gcc -o chbibkey chbibkey.o

chbibkey.o: chbibkey.c
	gcc -c chbibkey.c

clean:
	rm chbibkey.o chbibkey

