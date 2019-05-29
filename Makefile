CC = g++

CFLAGS = -c -Wall

all: run

run:
	$(CC) -std=c++11 main.cpp -o run

.PHONY : clean
clean:
	rm -rf *.o run
