#	-- ccompiler --
#
#	ccompiler's project Makefile.
#
#	Utilization example:
#		make <TARGET> ["DEBUG=true"]
#
#	@param TARGET
#		Can be any of the following:
#		all - builds the project (DEFAULT TARGET)
#		clean - cleans up all binaries generated during compilation
#		redo - cleans up and then builds
#		help - shows the utilization example
#
#	@param "DEBUG=true"
#		When present, the build will happen in debug mode.
#
#	@author
#		@hcpsilva - Henrique Silva
#		@birromer - Bernardo Hummes
#
#	Make's default action is "all" when no parameters are provided.


################################################################################
#	Definitions:

#	- Project's directories:
INC_DIR := include
OBJ_DIR := bin
OUT_DIR := build
SRC_DIR := src
LIB_DIR := lib

DEBUG :=

#	- Compilation flags:
#	Compiler and language version
CC := gcc -std=c17
FLX := flex
#	If DEBUG is defined, we'll turn on the debug flag and attach address
#	sanitizer on the executables.
DEBUGC := $(if $(DEBUG),-g -fsanitize=address -DDEBUG)
DEBUGL := $(if $(DEBUG),-d)
CFLAGS :=\
	-Wall \
	-Wextra \
	-Wpedantic \
	-Wshadow \
	-Wunreachable-code
LDFLAGS :=\
	-shared \
	-fPIC
OPT := $(if $(DEBUG),-O0,-O3 -march=native)
LIB := -L$(LIB_DIR) \
	-lfl
INC := -I$(INC_DIR)

################################################################################
#	Files:

#	- Main source files:
#	Presumes that all "main" source files are in the root of SRC_DIR
MAIN := $(wildcard $(SRC_DIR)/*.c)

#	- Path to all final binaries:
TARGET := $(patsubst %.c, $(OUT_DIR)/%, $(notdir $(MAIN)))

#	- Other source files:
SRC := $(shell find $(SRC_DIR) -name '*.c' | cut -d'/' -f2-)

#	- Objects to be created:
OBJ := $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))

#	- Lexer files:
LEX := $(shell find $(SRC_DIR) -name '*.l')

#	- Generated lexer sources:
GEN := $(patsubst %.l, %.yy.c, $(LEX))

################################################################################
#	Rules:

#	- Executables:
$(TARGET): $(OUT_DIR)/%: $(SRC_DIR)/%.c $(OBJ)
	$(CC) -o $@ $^ $(INC) $(LIB) $(DEBUGC) $(OPT)

#	- Generated lexer:
$(GEN): %.yy.c: %.l
	$(FLX) -o $@ $<

#	- Objects:
$(OBJ): $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) -c -o $@ $< $(INC) $(CFLAGS) $(DEBUGC) $(OPT)

################################################################################
#	Targets:

.DEFAULT_GOAL = all

all: $(GEN) $(TARGET)

clean:
	rm -rf $(OBJ_DIR)/* $(TARGET) $(GEN)

redo: clean all

help:
	@echo "ccompiler's project Makefile."
	@echo
	@echo "Utilization example:"
	@echo " make <TARGET> ['DEBUG=true']"
	@echo
	@echo "@param TARGET"
	@echo " Can be any of the following:"
	@echo " all - builds the project (DEFAULT TARGET)"
	@echo " clean - cleans up all binaries generated during compilation"
	@echo " redo - cleans up and then builds"
	@echo " help - shows the utilization example"
	@echo
	@echo "@param 'DEBUG=true'"
	@echo " When present, the build will happen in debug mode."

################################################################################
#	Debugging and etc.:

#	Debug of the Make variables
print-%:
	@echo $* = $($*)

.PHONY: all clean redo help print-%
