# Variables
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build
EXECUTABLE = emst

# Archivos fuente
SRCS = $(wildcard $(SRC_DIR)/*.cc)
# Archivos objeto
OBJS = $(SRCS:$(SRC_DIR)/%.cc=$(BUILD_DIR)/%.o)

# Reglas
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CXX) $(OBJS) -o $(EXECUTABLE)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cc
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)/*.o $(EXECUTABLE)

.PHONY: all clean