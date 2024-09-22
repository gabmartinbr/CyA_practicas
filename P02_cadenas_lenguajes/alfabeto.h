#ifndef ALFABETO_H
#define ALFABETO_H
#include <set>
#include <string>
#include <stdexcept>  // Para std::invalid_argument
#include <iostream>
#include "simbolo.h"

class Alfabeto {
private:
  // conjunto set de simbolos
  std::set<Simbolo> simbolos_;

public:
  // constructor de alfabeto a partir de los simbolos
  Alfabeto();

  // getter de conjunto de símbolos
  const std::set<Simbolo>& getSimbolos() const;

  // método para agregar un nuevo símbolo al set 
  void addSimbolo(const Simbolo& simbolo);

  // método para comprobar si ya está incluido un símbolo
  bool hasSimbolo(const Simbolo& simbolo) const;

  // sobrecarga de operador de salida para mostrar alfabeto = {a, b, c}
  friend std::ostream& operator<<(std::ostream& os, const Alfabeto& alfabeto);

};

#endif  // ALFABETO_H   