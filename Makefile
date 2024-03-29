CXX		  := g++
CXX_FLAGS := -Wall -Wextra -std=c++17 -ggdb

BIN		:= bin
SRC		:= src
INCLUDE	:= include
LIB		:= lib

LIBRARIES	:=
EXECUTABLE	:= main
ARGS		:= ./input/LargeNetwork.txt


all: $(BIN)/$(EXECUTABLE) $(ARGS)

run: clean all
	./$(BIN)/$(EXECUTABLE) $(ARGS)

$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp
	[ -d $(LIB) ] || mkdir -p $(LIB)
	[ -d $(BIN) ] || mkdir -p $(BIN)
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -L$(LIB) $^ -o $@ $(LIBRARIES)
	chmod a+x $(BIN)/$(EXECUTABLE)

clean:
	-rm $(BIN)/*
