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
  // Comenzar la impresión del conjunto de cadenas con una llave abierta
  os << "{";

  bool primera = true; // Flag para controlar la colocación de las comas

  // Imprimir la cadena vacía si está presente en el conjunto de cadenas
  if (lenguaje.cadenas_.find(Cadena()) != lenguaje.cadenas_.end()) {
    os << Cadena::CAD_VACIA;
    primera = false; // No poner coma después de la primera cadena
  }

  // Recorrer el conjunto de cadenas
  for (const auto& cadena : lenguaje.cadenas_) {
    // Omitir la cadena vacía, ya la hemos impreso
    if (cadena.getCadena().empty()) {
      continue;
    }

    // Si no es la primera vez, añadir una coma antes de la siguiente cadena
    if (!primera) {
      os << ", ";
    }
    os << cadena;  // Imprimir la cadena
    primera = false; // Asegurar que la próxima cadena reciba una coma antes
  }

  os << "}";  // Cerrar el conjunto de cadenas
  return os;
}
