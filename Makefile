CC = gcc
CFLAGS = -g -ggdb -ansi -pedantic -Wall 
INCLUDE_DIR =  $(shell pkg-config --cflags opencv) $(shell pkg-config --cflags gtk+-2.0) -lxdo #gtk contains glib 
LIBS =  $(shell pkg-config --libs opencv)$(shell pkg-config --libs gtk+-2.0) -lxdo #gtk contoins glib and X11

OBJ_DIR = obj
BIN_DIR = bin
SRC_DIR = src

#VERSION = debug
#VERSION = testing
#VERSION = version2
VERSION = finalversion

ifeq ($(VERSION),debug)
	SRCS = solver.c logic.c field.c test.c testing.c
endif

ifeq ($(VERSION),testing)
	SRCS = field.c logic.c solver.c  mainTerminal.c 
endif

ifeq ($(VERSION),version2)
	SRCS = field.c logic.c proba.c solver1.c mainVersion2.c imageRecognition.c screenInteraction.c
endif

ifeq ($(VERSION),finalversion)
	SRCS = field.c logic.c solver1.c main.c imageRecognition.c screenInteraction.c proba.c gtk_minesweeper_solver.c
endif

FINAL_TARGET = $(VERSION)

all: $(BIN_DIR)/$(FINAL_TARGET) 

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $(CFLAGS) $(INCLUDE_DIR) $< -o $@ 

$(BIN_DIR)/$(FINAL_TARGET): $(SRCS:%.c=$(OBJ_DIR)/%.o) 
	$(CC) $+ -o $@ $(LIBS)

clean:
	rm -f $(BIN_DIR)/$(FINAL_TARGET) $(OBJ_DIR)/*.o
