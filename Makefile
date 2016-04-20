allO=asciiWords.o Board.o bottomDisplay.o globals.o BindDisplay.o\
	 Interface.o Player.o Rack.o Scores.o Tile.o TileBag.o
CXX=g++
oDir=oFiles/
FLAGS=-c -g

all:
		make --no-print-directory unclear
		make --no-print-directory comp2
		make --no-print-directory comp
		make --no-print-directory clear

comp: $(allO)
		$(CXX) -o Words $(allO)

comp2: viewSave.o Tile.o globals.o
		$(CXX) -o viewSave viewSave.o Tile.o globals.o

asciiWords.o: asciiWords.cpp Interface.h globals.h \
 bottomDisplay.h Player.h Board.h Tile.h TileBag.h Rack.h Scores.h
		$(CXX) $(FLAGS) -o asciiWords.o asciiWords.cpp

viewSave.o: debugUtil/viewSave.cpp Tile.h
		$(CXX) $(FLAGS) -o viewSave.o debugUtil/viewSave.cpp 

Board.o: Board.cpp Board.h globals.h Tile.h
		$(CXX) $(FLAGS) -o  Board.o Board.cpp 

bottomDisplay.o: bottomDisplay.cpp bottomDisplay.h BindDisplay.h globals.h
		$(CXX) $(FLAGS) -o bottomDisplay.o bottomDisplay.cpp 

BindDisplay.o: BindDisplay.cpp BindDisplay.h globals.h
		$(CXX) $(FLAGS) -o BindDisplay.o BindDisplay.cpp 

Interface.o: Interface.cpp Interface.h globals.h bottomDisplay.h Player.h \
 Board.h Tile.h TileBag.h Rack.h Scores.h
		$(CXX) $(FLAGS) -o Interface.o Interface.cpp 

Player.o: Player.cpp Player.h globals.h Board.h Tile.h TileBag.h Rack.h
		$(CXX) $(FLAGS) -o Player.o Player.cpp 

Rack.o: Rack.cpp Rack.h globals.h Tile.h
		$(CXX) $(FLAGS) -o Rack.o Rack.cpp 

Scores.o: Scores.cpp Scores.h globals.h
		$(CXX) $(FLAGS) -o Scores.o Scores.cpp 

TileBag.o: TileBag.cpp TileBag.h globals.h Tile.h
		$(CXX) $(FLAGS) -o TileBag.o TileBag.cpp 

Tile.o: Tile.cpp Tile.h globals.h
		$(CXX) $(FLAGS) -o Tile.o Tile.cpp 

globals.o: globals.cpp globals.h
		$(CXX) $(FLAGS) -o globals.o globals.cpp 

unclear:
		@if ! mv $(oDir)*.o .; then printf "";fi
clear:
		@if ! mv *.o $(oDir); then printf "";fi
clean:
		rm *.o ;rm $(oDir)*.o


