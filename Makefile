ROOT_DIR := $(shell pwd)
export ROOT_DIR

CC = gcc 
CFLAGS = -Wall
LDFLAGS =
export CC
export CFLAGS
export LDFLAGS

SRC_DIR = src
INCLUDE_DIR = $(ROOT_DIR)/include
LIB_DIR = $(ROOT_DIR)/build/lib
BIN_DIR = $(ROOT_DIR)/build/bin
OBJ_DIR = $(ROOT_DIR)/build/obj
export INCLUDE_DIR
export LIB_DIR
export BIN_DIR
export OBJ_DIR

OBJECTS = $(wildcard $(OBJ_DIR)/*.o)

all: $(LIB_DIR)/libMShellCore.a $(BIN_DIR)/MShell

$(LIB_DIR)/libMShellCore.a: src
	ar rcs $(LIB_DIR)/libMShellCore.a $(OBJECTS)

$(BIN_DIR)/main.o: main.c
	$(CC) -c $(CFLAGS) -I$(INCLUDE_DIR) -o $@ $<

$(BIN_DIR)/MShell: $(BIN_DIR)/main.o $(LIB_DIR)/libMShellCore.a
	$(CC) $(LDFLAGS) -o $@ $(BIN_DIR)/main.o -L$(LIB_DIR) -lMShellCore

src:
	$(MAKE) -C $@

debug: 
	CFLAGS += -g -O0
	$(MAKE) all
clean:
	rm -rf $(OBJ_DIR)/* $(LIB_DIR)/* $(BIN_DIR)/*

.PHONY: all src debug clean
