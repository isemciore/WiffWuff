CC = g++
rCC = clang++



FLAGS = -std=c++11 -g -Wall

main.out: main.cpp obj/gamemaster.o obj/Item.o obj/Consumable.o obj/container.o obj/baseunit.o obj/PlayerCtrl.o obj/paladin.o obj/sorcerer.o obj/npc.o obj/wumpus.o obj/turtle.o obj/basetile.o obj/tile_dark_room.o obj/tile_escape_win.o obj/tile_mountain_ridge.o obj/tile_ocean.o
	$(CC) $(FLAGS) -o main.out main.cpp obj/gamemaster.o obj/Item.o obj/Consumable.o obj/container.o obj/baseunit.o obj/PlayerCtrl.o obj/paladin.o obj/sorcerer.o obj/npc.o obj/wumpus.o obj/turtle.o obj/basetile.o obj/tile_dark_room.o obj/tile_escape_win.o obj/tile_mountain_ridge.o obj/tile_ocean.o

obj/gamemaster.o : gamemaster.cpp obj/Item.o obj/Consumable.o obj/container.o obj/baseunit.o obj/PlayerCtrl.o obj/paladin.o obj/sorcerer.o obj/npc.o obj/wumpus.o obj/turtle.o obj/basetile.o obj/tile_dark_room.o obj/tile_escape_win.o obj/tile_mountain_ridge.o obj/tile_ocean.o
	$(CC) $(FLAGS) -c gamemaster.cpp -o obj/gamemaster.o


obj/Item.o : stuff/Item.cpp
	$(CC) $(FLAGS) -c stuff/Item.cpp -o obj/Item.o

obj/Consumable.o : stuff/Consumable.cpp obj/Item.o
	$(CC) $(FLAGS) -c stuff/Consumable.cpp -o obj/Consumable.o

obj/container.o : stuff/container.cpp obj/Item.o
	$(CC) $(FLAGS) -c stuff/container.cpp -o obj/container.o


obj/baseunit.o : character/baseunit.cpp
	$(CC) $(FLAGS) -c character/baseunit.cpp -o obj/baseunit.o

obj/PlayerCtrl.o : character/PlayerCtrl.cpp obj/baseunit.o
	$(CC) $(FLAGS) -c character/PlayerCtrl.cpp -o obj/PlayerCtrl.o

obj/paladin.o : character/paladin.cpp obj/PlayerCtrl.o
	$(CC) $(FLAGS) -c character/paladin.cpp -o obj/paladin.o

obj/sorcerer.o : character/sorcerer.cpp obj/PlayerCtrl.o
	$(CC) $(FLAGS) -c character/sorcerer.cpp -o obj/sorcerer.o

obj/npc.o : character/npc.cpp obj/baseunit.o
	$(CC) $(FLAGS) -c character/npc.cpp -o obj/npc.o

obj/wumpus.o : character/wumpus.cpp obj/npc.o
	$(CC) $(FLAGS) -c character/wumpus.cpp -o obj/wumpus.o

obj/turtle.o : character/turtle.cpp obj/npc.o
	$(CC) $(FLAGS) -c character/turtle.cpp -o obj/turtle.o



obj/basetile.o : enviroment/basetile.cpp
	$(CC) $(FLAGS) -c enviroment/basetile.cpp -o obj/basetile.o

obj/tile_dark_room.o : enviroment/tile_dark_room.cpp obj/basetile.o
	$(CC) $(FLAGS) -c enviroment/tile_dark_room.cpp -o obj/tile_dark_room.o

obj/tile_escape_win.o : enviroment/tile_escape_win.cpp obj/basetile.o
	$(CC) $(FLAGS) -c enviroment/tile_escape_win.cpp -o obj/tile_escape_win.o

obj/tile_mountain_ridge.o : enviroment/tile_mountain_ridge.cpp obj/basetile.o
	$(CC) $(FLAGS) -c enviroment/tile_mountain_ridge.cpp -o obj/tile_mountain_ridge.o

obj/tile_ocean.o : enviroment/tile_ocean.cpp obj/basetile.o
	$(CC) $(FLAGS) -c enviroment/tile_ocean.cpp -o obj/tile_ocean.o


clean:
	rm -f obj/*.o *.out && clear 

