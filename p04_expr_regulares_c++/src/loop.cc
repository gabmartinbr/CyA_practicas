#include "loop.h"

Loop::Loop(int line_counter, std::smatch& match) { 
  line_number_ = line_counter;

  // El primer grupo (match[1]) es el tipo de variable, el segundo (match[2]) es el nombre
  if (match.size() >= 1) {
    type_ = match[1].str();
  } else {
    std::cerr << "Error: no se pudo extraera el tipo y nombre de la variable" << match.size() << line_counter << std::endl;
  }
}
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