CC=g++
FLAGS=-std=c++17 -g -fsanitize=address
WARNINGS = -Wall -Wextra -Wunused -Werror

exec:  main.o bigInt.o #matrix.o proxyMatrix.o
	$(CC) $(FLAGS) -o exec main.o bigInt.o #matrix.o proxyMatrix.o

#proxyMatrix.o: proxyMatrix.cpp proxyMatrix.hpp
#	$(CC) $(FLAGS) $(WARNINGS) -c proxyMatrix.cpp

bigInt.o: bigInt.cpp bigInt.hpp
	$(CC) $(FLAGS) $(WARNINGS) -c bigInt.cpp

main.o: main.cpp bigInt.hpp test_runner.hpp
	$(CC) $(FLAGS) $(WARNINGS) -c main.cpp

test:
	./exec

clean:
	rm -rf *.o exec output.txt
