CXX		  := g++
CXX_FLAGS := -Wall -Wextra -std=c++17 -ggdb

BIN		:= bin
SRC		:= src
INCLUDE	:= include
LIB		:= lib

LIBRARIES	:=
EXECUTABLE	:= main
ARGS		:= ./input/cyclic.txt


all: $(BIN)/$(EXECUTABLE) $(ARGS)

run: clean all
	clear
	./$(BIN)/$(EXECUTABLE) $(ARGS)

$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp
	[ -d $(LIB) ] || mkdir -p $(LIB)
	[ -d $(BIN) ] || mkdir -p $(BIN)
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -L$(LIB) $^ -o $@ $(LIBRARIES)

clean:
	-rm $(BIN)/*
