CC = clang++
CXXFLAGS = -std=c++11 -Wall -Werror -fsanitize=address,undefined

all: main

main: matrix.o demo.o
	$(CC) $(CXXFLAGS) matrix.o demo.o -lm -o demo

clean:
	rm demo matrix.o demo.o