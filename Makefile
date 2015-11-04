allO=asciiWords.o Board.o bottomDisplay.o globals.o\
	 Interface.o Player.o Rack.o Scores.o Tile.o TileBag.o
CXX=g++
oDir=oFiles/

all:
		make --no-print-directory unclear
		make --no-print-directory comp
		make --no-print-directory clear

comp: $(allO)
		$(CXX) -o Words $(allO)

asciiWords.o: asciiWords.cpp Interface.h globals.h \
 bottomDisplay.h Player.h Board.h Tile.h TileBag.h Rack.h Scores.h

Board.o: Board.cpp Board.h globals.h Tile.h

bottomDisplay.o: bottomDisplay.cpp bottomDisplay.h globals.h

Interface.o: Interface.cpp Interface.h globals.h bottomDisplay.h Player.h \
 Board.h Tile.h TileBag.h Rack.h Scores.h

Player.o: Player.cpp Player.h globals.h Board.h Tile.h TileBag.h Rack.h

Rack.o: Rack.cpp Rack.h globals.h Tile.h

Scores.o: Scores.cpp Scores.h globals.h

TileBag.o: TileBag.cpp TileBag.h globals.h Tile.h

Tile.o: Tile.cpp Tile.h globals.h

globals.o: globals.cpp globals.h

unclear:
		@if ! mv $(oDir)*.o .; then printf "";fi
clear:
		@if ! mv *.o $(oDir); then printf "";fi
clean:
		rm *.o ;rm $(oDir)*.o

