CC := clang++
CFLAGS := -c -Werror -std=c++14
SRC_DIR := src
BUILD_DIR := build

all: pre_setup $(BUILD_DIR)/lox

$(BUILD_DIR)/lox: $(BUILD_DIR)/main.o $(BUILD_DIR)/scanner.o
	$(CC) $^ -o $@

$(BUILD_DIR)/main.o: $(SRC_DIR)/main.cpp
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/scanner.o: $(SRC_DIR)/scanner/scanner.cpp
	$(CC) $(CFLAGS) $< -o $@

pre_setup:
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)

# Run the lox interpreter
run:
	./$(BUILD_DIR)/lox

.PHONY: pre_setup
