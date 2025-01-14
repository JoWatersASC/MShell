CC ?=
CFLAGS ?=
LDFLAGS ?=

SRC_DIR ?= src
INCLUDE_DIR ?= include
LIB_DIR ?= build/lib
BIN_DIR ?= build/bin
OBJ_DIR ?= build/obj

SOURCE = shell.c
OBJECT = shell.o

BUILTIN_SDIR = built_ins

all: $(OBJ_DIR)/shell.o $(BUILTIN_SDIR)

$(OBJ_DIR)/shell.o: shell.c
	$(CC) -c $(CFLAGS) -I$(INCLUDE_DIR) -o $@ $<

$(BUILTIN_SDIR):
	$(MAKE) -C $@

.PHONY: all $(BUILTIN_SDIR)
