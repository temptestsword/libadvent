CC = gcc
CFLAGS = -Wall -Wextra -Werror
OUT_DIR = build
OUT_NAME = demo
PROJ_DIR = src
PROJ_FILES = demo.c

all: compile run

compile:
	$(CC) -O3 -o $(OUT_DIR)/$(OUT_NAME) $(PROJ_DIR)/$(PROJ_FILES)

devbuild:
	$(CC) $(CFLAGS) -O0 -g -o $(OUT_DIR)/$(OUT_NAME) $(PROJ_DIR)/$(PROJ_FILES)

run:
	clear
	./$(OUT_DIR)/$(OUT_NAME)

.PHONY: all compile devbuild run