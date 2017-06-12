SRCDIR = ../src/
SRC = $(addprefix ../src/, Main.cpp TexW.cpp Utils.cpp TTFTextW.cpp Entity.cpp Map.cpp)
CC = g++

CFLAGS = -Wall #Add -Wl,-subsystem,windows for stopping console
LFLAGS = -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf

BINDIR = ../bin/MountainBuilder

all : $(SRC)
	$(CC) $(SRC) $(CFLAGS) $(LFLAGS) -o $(BINDIR)
