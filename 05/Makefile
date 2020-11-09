CC=g++
FLAGS=-std=c++17 -g -fsanitize=address
WARNINGS = -Wall -Wextra -Werror -Wunused

exec:  main.o serializer.o
	$(CC) $(FLAGS) -o exec main.o serializer.o

serializer.o: serializer.cpp serializer.hpp
	$(CC) $(FLAGS) $(WARNINGS) -c serializer.cpp

main.o: main.cpp serializer.hpp test_runner.hpp
	$(CC) $(FLAGS) $(WARNINGS) -c main.cpp

test:
	./exec

clean:
	rm -rf *.o exec output.txt 
