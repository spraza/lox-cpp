CC := clang++
CFLAGS := -c -g -Werror -std=c++14
SRC_DIR := src
BUILD_DIR := build

all: pre_setup format $(BUILD_DIR)/lox

$(BUILD_DIR)/lox: $(BUILD_DIR)/main.o $(BUILD_DIR)/scanner.o $(BUILD_DIR)/token.o $(BUILD_DIR)/error_handler.o $(BUILD_DIR)/parser.o
	$(CC) $^ -o $@

$(BUILD_DIR)/main.o: $(SRC_DIR)/main.cpp
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/scanner.o: $(SRC_DIR)/scanner/scanner.cpp
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/token.o: $(SRC_DIR)/scanner/token.cpp
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/error_handler.o: $(SRC_DIR)/error_handler/error_handler.cpp
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/parser.o: $(SRC_DIR)/parser/parser.cpp $(BUILD_DIR)/token.o
	$(CC) $(CFLAGS) $< -o $@

format:
	find . -type f -name "*.?pp" | xargs clang-format -i

pre_setup:
	mkdir -p $(BUILD_DIR)
	$(CC) -std=c++14 $(SRC_DIR)/tools/ast_generator.cpp -o $(BUILD_DIR)/ast_generator
	./$(BUILD_DIR)/ast_generator $(SRC_DIR)

clean:
	rm -rf $(BUILD_DIR)

# Run the lox interpreter
run:
	./$(BUILD_DIR)/lox

.PHONY: pre_setup
