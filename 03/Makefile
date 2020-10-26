CC=g++
FLAGS=-std=c++17 -O3 -g -fsanitize=address
WARNINGS = -Wall -Wextra -Wunused -Werror

exec:  main.o matrix.o proxyMatrix.o
	$(CC) $(FLAGS) -o exec main.o matrix.o proxyMatrix.o

proxyMatrix.o: proxyMatrix.cpp proxyMatrix.hpp
	$(CC) $(FLAGS) $(WARNINGS) -c proxyMatrix.cpp

matrix.o: matrix.cpp matrix.hpp proxyMatrix.hpp
	$(CC) $(FLAGS) $(WARNINGS) -c matrix.cpp

main.o: main.cpp matrix.hpp test_runner.hpp
	$(CC) $(FLAGS) $(WARNINGS) -c main.cpp

test:
	./exec

clean:
	rm -rf *.o exec
