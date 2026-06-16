CC := gcc
FLAGS := -lm

BIN_PATH := bin
OBJ_PATH := obj
SRC_PATH := src

TARGET := $(BIN_PATH)/generation_aleatoire

SRC := $(shell find $(SRC_PATH) -name *.c)
OBJ := $(SRC:%.c=%.o)

default: makedir $(TARGET) clean run

.PHONY: makedir

makedir:
	@mkdir -p $(BIN_PATH) $(OBJ_PATH)

.PHONY: clean

clean:
	@rm -rf $(OBJ_PATH)

.PHONY: run
run:
	./$(TARGET)

.PHONY: debug
debug:
	gdbgui ./$(TARGET)


$(TARGET): $(OBJ)
	$(CC) -o $@ $(foreach obj, $^, $(OBJ_PATH)/$(notdir $(obj))) $(FLAGS)

%.o: %.cpp
	$(CC) -c $< -o $(OBJ_PATH)/$(notdir $@)

%.o: %.c
	$(CC) -c $< -o $(OBJ_PATH)/$(notdir $@)