CC=g++

sha256_bruteforcer: sha256.o bruteforce.o main.o
	$(CC) -o ../build/bruteforcer sha256.o bruteforce.o main.o
	clean

sha256.o: sha256.c
	$(CC) -o sha256.o -c sha256.c

bruteforce.o: bruteforce.c
	$(CC) -o bruteforce.o -c bruteforce.c

main.o:	main.c
	$(CC) -o main.o -c main.c

clean:
	rm -f *.o bruteforcer
