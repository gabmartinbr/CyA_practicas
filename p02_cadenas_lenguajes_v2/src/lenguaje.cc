#include "lenguaje.h"

/**
 * @brief Constructor por defecto de la clase Lenguaje.
 */
Lenguaje::Lenguaje() {}

/**
 * @brief Constructor de la clase Lenguaje a partir de un conjunto de cadenas.
 * 
 * @param cadenas Conjunto de cadenas que conforman el lenguaje.
 */
Lenguaje::Lenguaje(const std::set<Cadena>& cadenas) : cadenas_(cadenas) {}

/**
 * @brief Getter para obtener el conjunto de cadenas del lenguaje.
 * 
 * @return const std::set<Cadena>& Referencia constante al conjunto de cadenas.
 */
const std::set<Cadena>& Lenguaje::getCadenas() const {
  return cadenas_;
}

/**
 * @brief Método para añadir una nueva cadena al lenguaje.
 * 
 * @param cadena La cadena a añadir al conjunto.
 */
void Lenguaje::addCadena(const Cadena& cadena) {
  cadenas_.insert(cadena);
}

/**
 * @brief Método para comprobar si una cadena ya está en el lenguaje.
 * 
 * @param cadena La cadena a comprobar.
 * @return true Si la cadena está en el lenguaje.
 * @return false Si la cadena no está en el lenguaje.
 */
bool Lenguaje::hasCadena(const Cadena& cadena) const {
  return cadenas_.count(cadena) > 0;  // > 0 indica que existe en el conjunto
}

/**
 * @brief Sobrecarga del operador << para mostrar el lenguaje de forma legible.
 * 
 * @param os Flujo de salida.
 * @param lenguaje Objeto Lenguaje a mostrar.
 * @return std::ostream& Referencia al flujo de salida.
 */
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
