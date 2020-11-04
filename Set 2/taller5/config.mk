CC = gcc
CFLAGS = -Wall -c -I$(I_DIR) $^ -g  -o $@
OFLAGS = $^ -o $@

EXE_DIR = ./bin
I_DIR = ./include
SRC_DIR = ./src
OBJ_DIR = ./obj

EXE_FILES = $(EXE_DIR)/bytes
LIB_FILES = $(wildcard $(I_DIR)/*.h)
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))
