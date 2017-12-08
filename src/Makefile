CC=g++

sha256_bruteforcer: sha256.o bruteforce.o main.o
	$(CC) -o ../build/bruteforcer sha256.o bruteforce.o main.o
	clean

sha256.o: sha256.cpp
	$(CC) -o sha256.o -c sha256.cpp

bruteforce.o: bruteforce.cpp
	$(CC) -o bruteforce.o -c bruteforce.cpp

main.o:	main.cpp
	$(CC) -o main.o -c main.cpp

clean:
	rm -f *.o bruteforcer
