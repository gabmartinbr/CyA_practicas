#ifndef SIMBOLO_H
#define SIMBOLO_H   

#include <iostream>

class Simbolo {
private:
  char simbolo_;

public:
  // constructor de simbolo
  Simbolo(char simbolo);

  // getter
  char getSimbolo() const;

  // sobrecarga del operador< para el uso de simbolos en set
  bool operator<(const Simbolo& otro) const;

  // sobrecarga del operador<< para imprimir simbolos
  friend std::ostream& operator<<(std::ostream& os, const Simbolo& simbolo);

};
#endif  // SIMBOLO_H