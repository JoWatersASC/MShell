CC ?=
CFLAGS ?=
LDFLAGS ?=

SRC_DIR ?= 
INCLUDE_DIR ?=
LIB_DIR ?=
BIN_DIR ?=
OBJ_DIR ?=

all: hash map

hash: $(OBJ_DIR)/hash.o
map: $(OBJ_DIR)/map.o

$(OBJ_DIR)/hash.o: hash.c
	$(CC) -c $(CFLAGS) -I$(INCLUDE_DIR) -o $@ $<

$(OBJ_DIR)/map.o: map.c
	$(CC) -c $(CFLAGS) -I$(INCLUDE_DIR) -o $@ $<

.PHONY: all hash map