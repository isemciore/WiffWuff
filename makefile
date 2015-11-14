rCC = g++
CC = clang++



FLAGS = -std=c++11 -g -Wall

main.out: main.cpp obj/BaseUnit.o obj/BaseTile.o character/BaseUnit.cpp enviroment/BaseTile.cpp
	$(CC) $(FLAGS) -o main.out main.cpp obj/BaseTile.o obj/BaseUnit.o

obj/BaseUnit.o : character/BaseUnit.cpp
	$(CC) $(FLAGS) -c character/BaseUnit.cpp -o obj/BaseUnit.o

obj/BaseTile.o : enviroment/BaseTile.cpp
	$(CC) $(FLAGS) -c enviroment/BaseTile.cpp -o obj/BaseTile.o



clean:
	rm -f obj/*.o *.out && clear 

