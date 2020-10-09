CC=g++
FLAGS=-std=c++17 -g -mfpmath=sse -fstack-protector-all -g -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -Woverloaded-virtual -Wnon-virtual-dtor -Wcast-qual -Wno-suggest-attribute=format #-fsanitize=address

all: test

test:  main.o
	$(CC) $(FLAGS) -o test main.o

main.o: main.cpp test_runner.hpp allocator.hpp
	$(CC) $(FLAGS) -c main.cpp

clean:
	rm -rf *.o a.out
