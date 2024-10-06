#include "loop.h"

Loop::Loop(int line_number, const std::string& type) 
  : line_number_(line_number), type_(type) {}

int Loop::GetLineNumber() const {
  return line_number_;
}

std::string Loop::GetType() const {
  return type_;
}

std::ostream& operator<<(std::ostream& os, const Loop& loop) {
    os << "[ Line " << loop.GetLineNumber() << "] LOOP : " << loop.GetType();
    return os;
}