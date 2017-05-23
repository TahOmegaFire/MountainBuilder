SRCDIR = ../src/
SRC = $(addprefix ../src/, Main.cpp TexW.cpp Utils.cpp TTFTextW.cpp Entity.cpp Map.cpp)
CC = g++

CFLAGS = -Wall #Add -Wl,-subsystem,windows for stopping console
LFLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf

IDIR = ../lib/i686-w64-mingw32/include/SDL2
LDIR = ../lib/i686-w64-mingw32/lib

BINDIR = ../bin/MountainBuilder

all : $(SRC)
	$(CC) $(SRC) -I$(IDIR) -L$(LDIR) $(CFLAGS) $(LFLAGS) -o $(BINDIR)
