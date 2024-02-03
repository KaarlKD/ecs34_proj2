CC = cc
CXX = g++

INC_DIR = ./include
SRC_DIR = ./src
OBJ_DIR = ./obj
BIN_DIR = ./bin
TEST_SRC_DIR = ./testsrc

CXXFLAGS = -std=c++17 -I$(INC_DIR)
LDFLAGS = -lgtest -lgtest_main -lpthread

all: directories runtests

runtests: $(BIN_DIR)/teststrdatasource $(BIN_DIR)/teststrdatasink
	$(BIN_DIR)/teststrdatasource
	$(BIN_DIR)/teststrdatasink










clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(BIN_DIR)

directories:
	mkdir -p $(OBJ_DIR)
	mkdir -p $(BIN_DIR)