# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g
INCLUDES = -Iinclude

# Directories
SRC_DIR = src
BIN_DIR = bin
INCLUDE_DIR = include

# Target executable name
TARGET = $(BIN_DIR)/snake

# Automatically find all source files (including main.cpp in root)
SOURCES = $(wildcard $(SRC_DIR)/*.cpp) $(wildcard main.cpp)
OBJECTS = $(patsubst %.cpp,$(BIN_DIR)/%.o,$(notdir $(SOURCES)))

# Default target
all: $(TARGET)

# Create bin directory if it doesn't exist
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Link the executable
$(TARGET): $(OBJECTS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(TARGET)

# Generic rule for source files
$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Special rule for main.cpp in root
$(BIN_DIR)/main.o: main.cpp | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Clean build artifacts
clean:
	rm -rf $(BIN_DIR)

# Clean and rebuild
rebuild: clean all

# Run the game
run: $(TARGET)
	./$(TARGET)

# Show project info
info:
	@echo "Snake Game Project"
	@echo "=================="
	@echo "Source files: $(SOURCES)"
	@echo "Header files: $(wildcard $(INCLUDE_DIR)/*.h)"
	@echo "Object files: $(OBJECTS)"
	@echo "Target: $(TARGET)"
	@echo "Compiler: $(CXX)"
	@echo "Flags: $(CXXFLAGS)"

# Help target
help:
	@echo "Available targets:"
	@echo "  all      - Build the game (default)"
	@echo "  clean    - Remove build artifacts"
	@echo "  rebuild  - Clean and rebuild"
	@echo "  run      - Build and run the game"
	@echo "  info     - Show project information"
	@echo "  help     - Show this help message"

# Phony targets
.PHONY: all clean rebuild run info help
