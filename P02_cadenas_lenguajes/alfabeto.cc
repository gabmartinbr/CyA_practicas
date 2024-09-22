#include "alfabeto.h"

// constructor
Alfabeto::Alfabeto() {}

// getter de conjunto de símbolos
const std::set<Simbolo>& Alfabeto::getSimbolos() const {
  return simbolos_;
}

// método para agregar un nuevo símbolo al set 
void Alfabeto::addSimbolo(const Simbolo& simbolo) {
  if (simbolo.getSimbolo() != '\0') {
    simbolos_.insert(simbolo);
  } else {
    throw std::invalid_argument("El símbolo no puede ser vacío para añadifr al alfabeto");
  }
}

// método para comprobar si ya está incluido un símbolo
bool Alfabeto::hasSimbolo(const Simbolo& simbolo) const{
  auto it = simbolos_.find(simbolo);
  return it != simbolos_.end(); // retorna true cuando it no es el final, es decir, encontró el simbolo
}

// sobrecarga de operador de salida para mostrar alfabeto = {a, b, c}
std::ostream& operator<<(std::ostream& os, const Alfabeto& alfabeto) {
  os << "{";
  bool inicio = true; // control de separadores
  for (const auto& simbolo : alfabeto.simbolos_) {  // recorrer todos los simbolos de alfabeto
    if (!inicio) {  // si no es el primero, imprimir separador
      os << ", ";
    }
    // tras separador, acceder e imprimir simbolo
    os << simbolo.getSimbolo();
    // cambiar a false para el resto de simbolos, ya que no son los primeros
    inicio = false;
  }
  // cierre de alfabeto
  os << "}";
  return os;
}