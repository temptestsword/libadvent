CC = gcc
CFLAGS = -Wall -Wextra 
OUT_DIR = build
OUT_NAME = demo
PROJ_DIR = src
PROJ_FILES = demo.c

all: compile run

compile:
	$(CC) -O3 -o $(OUT_DIR)/$(OUT_NAME) $(PROJ_DIR)/$(PROJ_FILES)

devbuild:
	$(CC) $(CFLAGS) -o $(OUT_DIR)/$(OUT_NAME) $(PROJ_DIR)/$(PROJ_FILES)

run:
	clear
	./$(OUT_DIR)/$(OUT_NAME)