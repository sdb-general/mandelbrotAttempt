CC = g++
CFLAGS = -pthread

main: main.o
	$(CC) $(CFLAGS) -o main main.o

main.o: main.cxx
	$(CC) $(CFLAGS) -c main.cxx
