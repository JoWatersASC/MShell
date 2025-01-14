CC ?= gcc
CFLAGS ?= -Wall
LDFLAGS ?=

INCLUDE_DIR ?= include
LIB_DIR ?= 
BIN_DIR ?= 
OBJ_DIR ?= 

BUILTIN_DIR = built_ins

SOURCES = $(wildcard *.c)
OBJECTS = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SOURCES))

all: $(OBJECTS)

$(OBJ_DIR)/%.o: %.c
	$(CC) -c $(CFLAGS) -I$(INCLUDE_DIR) -o $@ $<
