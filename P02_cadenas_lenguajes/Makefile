# Variables
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++20
SRC = main.cc cadena.cc simbolo.cc alfabeto.cc lenguaje.cc
TARGET = p2_cadenas_lenguajes

# Reglas
all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(TARGET)

.PHONY: all clean
