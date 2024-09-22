#include "lenguaje.h"

// constructor de conjunto de cadenas
Lenguaje::Lenguaje() {}
Lenguaje::Lenguaje(const std::set<Cadena>& cadenas) :
  cadenas_(cadenas) {}

// getter para obtener el conjunto de cadenas de un lenguaje
const std::set<Cadena>& Lenguaje::getCadenas() const {
  return cadenas_;
}

// método para añadir nueva cadena al lenguaje
void Lenguaje::addCadena(const Cadena& cadena) {
  cadenas_.insert(cadena);
}

// método para comprobar si una cadena ya está en el lenguaje
bool Lenguaje::hasCadena(const Cadena& cadena) const {
  return cadenas_.count(cadena) > 0;  // > 0 es que existe en el conjunto
}

// sobrecarga el operador<< para mostrar lenguaje = {&, a, aa, aab}
std::ostream& operator<<(std::ostream& os, const Lenguaje& lenguaje) {
  // imprimir llave inicial y cadena vacía
  os << "{" << Cadena::CAD_VACIA;
  bool inicio = true; // control de separadores
  for (const auto& cadena : lenguaje.cadenas_) {  // recorrer todas las cadenas del lenguaje
    if (!inicio) {
      os << ", ";
    }
    os << cadena;
    inicio = false;
  }
  os << "}";
  return os;
}