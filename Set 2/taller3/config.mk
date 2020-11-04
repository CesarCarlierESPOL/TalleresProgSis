CC = gcc
CFLAGS = -c $< -g -Wall -std=c99 -I$(I_DIR) -o $@

EXE_DIR = bin
I_DIR = include
SRC_DIR = src
O_DIR = obj

EXE_FILES = $(EXE_DIR)/cifrado
LIB_FILES = $(wildcard $(IDIR)/*.h)
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(O_DIR)/%.o, $(SRC_FILES))
