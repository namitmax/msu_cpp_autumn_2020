CC=g++
FLAGS=-std=c++17 -g -pthread -fsanitize=thread
WARNINGS = -Wall -Wextra -Wunused -Werror

exec:  main.o
	$(CC) $(FLAGS) -o exec main.o

main.o: main.cpp threadPool.hpp test_runner.hpp
	$(CC) $(FLAGS) $(WARNINGS) -c main.cpp

test:
	./exec

clean:
	rm -rf *.o exec output.txt 
