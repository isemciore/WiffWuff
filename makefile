rCC = g++
CC = clang++



FLAGS = -std=c++11 -g -Wall

main.out: main.cpp obj/base_unit.o obj/base_tile.o character/base_unit.cpp enviroment/base_tile.cpp
	$(CC) $(FLAGS) -o main.out main.cpp obj/base_tile.o obj/base_unit.o 

obj/base_unit.o : character/base_unit.cpp
	$(CC) $(FLAGS) -c character/base_unit.cpp -o obj/base_unit.o

obj/base_tile.o : enviroment/base_tile.cpp
	$(CC) $(FLAGS) -c enviroment/base_tile.cpp -o obj/base_tile.o



clean:
	rm -f obj/*.o *.out && clear 

