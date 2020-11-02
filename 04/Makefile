CC=g++
FLAGS=-std=c++17 -g -fsanitize=address
WARNINGS = -Wall -Wextra -Wunused -Werror

exec:  main.o bigInt.o 
	$(CC) $(FLAGS) -o exec main.o bigInt.o 

bigInt.o: bigInt.cpp bigInt.hpp
	$(CC) $(FLAGS) $(WARNINGS) -c bigInt.cpp

main.o: main.cpp bigInt.hpp test_runner.hpp
	$(CC) $(FLAGS) $(WARNINGS) -c main.cpp

test:
	./exec

clean:
	rm -rf *.o exec output.txt
