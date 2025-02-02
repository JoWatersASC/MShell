# ROOT_DIR := $(shell pwd)
ROOT_DIR := $(CURDIR)
export ROOT_DIR

CC = gcc 
CFLAGS = -Wall
LDFLAGS =
export CC
export CFLAGS
export LDFLAGS

INCLUDE_DIR = $(ROOT_DIR)/include
LIB_DIR = $(ROOT_DIR)/build/lib
BIN_DIR = $(ROOT_DIR)/build/bin
OBJ_DIR = $(ROOT_DIR)/build/obj
export INCLUDE_DIR
export LIB_DIR
export BIN_DIR
export OBJ_DIR

OBJECTS = $(wildcard $(OBJ_DIR)/*.o)

all: $(BIN_DIR)/MShell

core: $(LIB_DIR)/libMShellCore.a
mshell: $(BIN_DIR)/MShell

$(LIB_DIR)/libMShellCore.a: src
	ar rcs $(LIB_DIR)/libMShellCore.a $(OBJECTS)

$(BIN_DIR)/MShell: $(BIN_DIR)/main.o $(LIB_DIR)/libMShellCore.a
	$(CC) $(LDFLAGS) $(BIN_DIR)/main.o -L$(LIB_DIR) -lMShellCore -o $@

$(BIN_DIR)/main.o: main.c
	$(CC) -c $(CFLAGS) -I$(INCLUDE_DIR) -o $@ $<


src:
	$(MAKE) -C $@
hash:
	$(MAKE) -C src $@


debug: CFLAGS += -g -O0
debug: all

clean:
	rm -rf $(OBJ_DIR)/* $(LIB_DIR)/* $(BIN_DIR)/*

install:
	cp $(BIN_DIR)/MShell $(DESTDIR)/usr/local/bin/
	shell chmod 755 $(DESTDIR)/usr/local/bin/MShell

.PHONY: all core mshell
.PHONY: src hash
.PHONY: debug clean install
