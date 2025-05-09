# Compiler settings
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

# Project files
SRC_DIR = .
OBJ_DIR = obj
BIN_DIR = bin

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
TARGET = $(BIN_DIR)/big2

# Header files
HEADERS = $(wildcard $(SRC_DIR)/*.h)

# Create directories
$(shell mkdir -p $(OBJ_DIR) $(BIN_DIR))

# Main target
all: $(TARGET)

# Link object files
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

# Compile source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Run the program
run: $(TARGET)
	./$(TARGET)

# Debug build
debug: CXXFLAGS += -g -DDEBUG
debug: clean all

# Release build
release: CXXFLAGS += -DNDEBUG
release: clean all

.PHONY: all clean run debug release 