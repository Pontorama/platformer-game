#Compiler used
CC = g++

#Linked objects
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf

#Compiler flags
COMPILER_FLAGS = -w -Iinclude -Ilib -std=c++14

#Name of output file
OUTPUT = bin/main

#Objects to compile
OBJS = src/*.cpp src/ui/*.cpp#src/main.cpp src/Game.cpp src/GameObject.cpp src/Player.cpp src/TextureManager.cpp src/Vector2.cpp src/Platform.cpp src/Hitbox.cpp src/LevelLoader.cpp

all:
	${CC} ${COMPILER_FLAGS} ${OBJS} ${LINKER_FLAGS} -o ${OUTPUT}

debug:
	${CC} ${COMPILER_FLAGS} ${OBJS} ${LINKER_FLAGS} -g -o bin/main.debug
