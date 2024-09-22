#ifndef LENGUAJE_H
#define LENGUAJE_H

#include "cadena.h"
#include <iostream>

class Lenguaje {
private:
  std::set<Cadena> cadenas_;  // set de cadenas que forman el lenguaje

public:
  // constructor de conjunto de cadenas
  Lenguaje();

  // getter para obtener conjunto de cadenas de un lenguaje
  const std::set<Cadena>& getCadenas() const;

  // método para añadir nueva cadena al lenguaje
  void addCadena(const Cadena& cadena);

  // método para comprobar si ya existe una cadena en el lenguaje
  bool hasCadena(const Cadena& cadena) const;

  // sobrecarga de operador<< para mostrar lenguaje = {epsilon, a, aa, aab}
  friend std::ostream& operator<<(std::ostream& os, const Lenguaje& lenguaje);
};


#endif  // LENGUAJE_H 
