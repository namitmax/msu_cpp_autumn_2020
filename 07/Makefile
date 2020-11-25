CC=g++
FLAGS=-std=c++17 -g -fsanitize=address
WARNINGS = -Wall -Wextra -Werror -Wunused

exec:  main.o
	$(CC) $(FLAGS) -o exec main.o

main.o: main.cpp vector.hpp test_runner.hpp
	$(CC) $(FLAGS) $(WARNINGS) -c main.cpp

test:
	./exec

clean:
	rm -rf *.o exec output.txt 
