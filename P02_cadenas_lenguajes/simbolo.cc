#include "simbolo.h"
#include <stdexcept>  // Para std::invalid_argument


Simbolo::Simbolo(char simbolo) {
  if (simbolo == '\0') {
    throw std::invalid_argument("No pueden haber símbolos vacíos.");
  }
  simbolo_ = simbolo;
}

char Simbolo::getSimbolo() const {
  return simbolo_;
}

bool Simbolo::operator<(const Simbolo& otro) const {
  return simbolo_ < otro.getSimbolo();
}

std::ostream& operator<<(std::ostream& os, const Simbolo& simbolo) {
  os << simbolo.getSimbolo();
  return os;
}