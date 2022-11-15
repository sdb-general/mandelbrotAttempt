CC = g++
CFLAGS = -pthread $(shell pkg-config --cflags sdl2)
LDFLAGS = $(shell pkg-config --libs sdl2)

main: main.o
	$(CC) -o main main.o $(CFLAGS) $(LDFLAGS)

main.o: main.cxx
	$(CC) -c main.cxx $(CFLAGS) $(LDFLAGS)
