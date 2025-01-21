CC ?=
CFLAGS ?=
LDFLAGS ?=

SRC_DIR ?= .
INCLUDE_DIR ?= ../include
LIB_DIR ?= ../build/lib
BIN_DIR ?= ../build/bin
OBJ_DIR ?= ../build/obj

BUILTIN_SDIR = built_ins
HASH_SDIR = hash

all: shell $(BUILTIN_SDIR) $(HASH_SDIR)

shell: $(OBJ_DIR)/shell.o

$(OBJ_DIR)/shell.o: shell.c
	$(CC) -c $(CFLAGS) -I$(INCLUDE_DIR) -o $@ $<


$(BUILTIN_SDIR):
	$(MAKE) -C $@
$(HASH_SDIR):
	$(MAKE) -C $@

.PHONY: all shell $(BUILTIN_SDIR) $(HASH_SDIR)