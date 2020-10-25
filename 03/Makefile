CC=g++
FLAGS=-std=c++17 -O3 -g -fsanitize=address
WARNINGS = -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -Woverloaded-virtual -Wnon-virtual-dtor -Wcast-qual -Wno-suggest-attribute=format

exec:  main.o
	$(CC) $(FLAGS) -o exec main.o

main.o: main.cpp matrix.hpp proxyMatrix.hpp test_runner.hpp
	$(CC) $(FLAGS) $(WARNINGS) -c main.cpp

test:
	./exec

clean:
	rm -rf *.o exec
