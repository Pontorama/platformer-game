#Compiler used
CC = g++

#Linked objects
LINKER_FLAGS = -lSDL2 -lSDL2_image

#Compiler flags
COMPILER_FLAGS = -w

#Name of output file
OUTPUT = main.exec

#Objects to compile
OBJS = main.cpp

all: main.cpp
	${CC} ${OBJS} ${COMPILER_FLAGS} ${LINKER_FLAGS} -o ${OUTPUT}