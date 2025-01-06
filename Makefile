CC = gcc 
CFLAGS = -Wall
LDFLAGS =

SRC_DIR = src
INCLUDE_DIR = include
LIB_DIR = build/lib
BIN_DIR = build/bin
OBJ_DIR = build/obj

SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, SOURCES)

all: $(LIB_DIR)/MShellCore $(BIN_DIR)/MShell

$(LIB_DIR)/MShellCore: $(OBJECTS)
	ar rcs $(LIB_DIR)/MShellCore.a $(OBJECTS)

$(BIN_DIR)/MShell: .main.o $(LIB_DIR)/MShellCore.a
	$(CC) $(LDFLAGS) -L$(LIB_DIR) -lMShellCore -o $@ .main.o

$(OBJ_DIR)/%o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

.main.o: main.c
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -o $@ $<

debug: CFLAGS += -g -O0
	$(MAKE) all
clean:
	rm -rf $(OBJ_DIR)/* $(LIB_DIR)/* $(BIN_DIR)/*

.PHONY: all debug clean
