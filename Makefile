SRC = main.cpp player.cpp level.cpp
OBJ = main.o player.o level.o

APP = app

all:
	@g++ -std=c++2a -c -Wall -Wno-narrowing $(SRC)
	@g++ $(OBJ) -o $(APP) -lsfml-audio -lsfml-system -lsfml-window -lsfml-graphics
	@./$(APP)
