# CC and flags
CC = gcc
CXXFLAGS = -g -Wall

# folders
INCLUDE_FOLDER = ./include/
BIN_FOLDER = ./bin/
OBJ_FOLDER = ./obj/
SRC_FOLDER = ./src/


# all sources, objs, and header files
MAIN = main
TARGET = run
SRC = $(wildcard $(SRC_FOLDER)*.c)
OBJ = $(patsubst $(SRC_FOLDER)%.c, $(OBJ_FOLDER)%.o, $(SRC))

# compile
$(OBJ_FOLDER)%.o: $(SRC_FOLDER)%.c
	$(CC) $(CXXFLAGS) -c $< -o $@ -I$(INCLUDE_FOLDER)

all: $(OBJ)
	$(CC) $(CXXFLAGS) -o $(BIN_FOLDER)$(TARGET) $(OBJ) 

clean:
	@rm -rf $(OBJ_FOLDER)* $(BIN_FOLDER)*

run:
	@$(BIN_FOLDER)$(TARGET)