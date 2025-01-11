CC = gcc 
CFLAGS = -Wall
LDFLAGS =

SRC_DIR = src
INCLUDE_DIR = include
LIB_DIR = build/lib
BIN_DIR = build/bin
OBJ_DIR = build/obj

SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SOURCES))

all: $(LIB_DIR)/libMShellCore.a $(BIN_DIR)/MShell

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c -o $@ $<

$(LIB_DIR)/libMShellCore.a: $(OBJECTS)
	ar rcs $(LIB_DIR)/libMShellCore.a $(OBJECTS)

main.o: main.c
	$(CC) -c $(CFLAGS) -I$(INCLUDE_DIR) -o $@ $<

$(BIN_DIR)/MShell: main.o $(LIB_DIR)/libMShellCore.a
	$(CC) $(LDFLAGS) -o $@ main.o -L$(LIB_DIR) -lMShellCore



debug: 
	CFLAGS += -g -O0
	$(MAKE) all
clean:
	rm -rf $(OBJ_DIR)/* $(LIB_DIR)/* $(BIN_DIR)/* main.o

.PHONY: all debug clean
