#Compiler used
CC = g++

#Linked objects
LINKER_FLAGS = -lSDL2 -lSDL2_image

#Compiler flags
COMPILER_FLAGS = -w

#Name of output file
OUTPUT = main.exec

#Objects to compile
OBJS = main.cpp src/Game.h src/Game.cpp src/GameObject.h src/GameObject.cpp src/Player.h src/Player.cpp src/TextureManager.h src/TextureManager.cpp src/Vector2.h src/Vector2.cpp src/Platform.h src/Platform.cpp src/Hitbox.h src/Hitbox.cpp

all: main.cpp
	${CC} ${OBJS} ${COMPILER_FLAGS} ${LINKER_FLAGS} -o ${OUTPUT}
