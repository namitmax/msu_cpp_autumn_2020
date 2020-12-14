CC=g++
FLAGS=-std=c++17 -g -pthread -O3 -fsanitize=thread
WARNINGS = -Wall -Wextra -Wunused -Werror

exec:  main.o
	$(CC) $(FLAGS) -o exec main.o

main.o: main.cpp file_sort.hpp test_runner.hpp
	$(CC) $(FLAGS) $(WARNINGS) -c main.cpp

test:
	./exec

clean:
	rm -rf *.o exec output.txt input.txt temp_*
