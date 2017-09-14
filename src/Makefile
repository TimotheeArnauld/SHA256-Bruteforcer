CC=g++
$CFLAGS=-I.

sha256_bruteforcer: main.o sha256.o
	$(CC) -o bruteforcer main.o sha256.o $(CFLAGS)

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
