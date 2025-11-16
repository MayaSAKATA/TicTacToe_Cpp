CXX=g++
#Compilation options
CXXFLAGS=-W -Wall -ansi -pedantic -std=c++17
LDFLAGS=
EXEC=tictactoe_game

#Folders
BUILD_DIR=build
SRC_DIR=src
INC_DIR=include

OBJECTS=$(BUILD_DIR)/main.o $(BUILD_DIR)/TicTacToe.o

#Rules
all: $(BUILD_DIR) $(EXEC)

#Create build folder if it doesn't exist
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(EXEC): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@

#Compilation rules
$(BUILD_DIR)/main.o: $(SRC_DIR)/main.cpp $(INC_DIR)/TicTacToe.hpp
	$(CXX) -o $@ -c $< -I$(INC_DIR) $(CXXFLAGS)

$(BUILD_DIR)/TicTacToe.o: $(SRC_DIR)/TicTacToe.cpp $(INC_DIR)/TicTacToe.hpp
	$(CXX) -o $@ -c $< -I$(INC_DIR) $(CXXFLAGS)

clean:
	rm -rf $(EXEC) $(BUILD_DIR)