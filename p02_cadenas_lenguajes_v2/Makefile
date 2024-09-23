# Variables
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
SRC_DIR = src
INC_DIR = include
DOCS_DIR = docs
BUILD_DIR = build
EXECUTABLE = p02_cadenas_lenguajes

# Archivos fuente
SRCS = $(wildcard $(SRC_DIR)/*.cc)
# Archivos objeto
OBJS = $(SRCS:$(SRC_DIR)/%.cc=$(BUILD_DIR)/%.o)

# Reglas
all: $(EXECUTABLE) docs

$(EXECUTABLE): $(OBJS)
	$(CXX) $(OBJS) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cc
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -c $< -o $@

docs:
	doxygen Doxyfile

clean:
	rm -rf $(BUILD_DIR)/*.o $(EXECUTABLE) $(DOCS_DIR)/*

.PHONY: all clean docs
