// cadena.cc
#include "cadena.h"

// definición de cadena vacía
const Simbolo Cadena::CAD_VACIA = Simbolo('&');

// constructor para formar cadena 
Cadena::Cadena(const std::vector<Simbolo>& simbolos)
  : cadena_(simbolos), alfabeto_() {
    // Construir el alfabeto a partir de los símbolos de la cadena
    for (const auto& simbolo : simbolos) {
        alfabeto_.addSimbolo(simbolo);
    }
}

// getters para obtener la cadena y su respectivo alfabeto
const std::vector<Simbolo>& Cadena::getCadena() const {
  return cadena_;
}
const Alfabeto& Cadena::getAlfabeto() const {
  return alfabeto_;
}

void Cadena::addSimbolo(const Simbolo& simbolo) {
  cadena_.push_back(simbolo);
}

// métodos para obtener sufijos y prefijos
// prefijo de w = abc -> &,a,ab,abc
std::set<std::vector<Simbolo>> Cadena::getPrefijos() const {
  std::set<std::vector<Simbolo>> prefijos;
  std::vector<Simbolo> prefijo;

  prefijos.insert({CAD_VACIA});  // Insertar el prefijo vacío
  for (size_t i = 0; i < cadena_.size(); i++) {
    prefijo.push_back(cadena_[i]);
    prefijos.insert(prefijo);
  }
  return prefijos;
}

std::set<std::vector<Simbolo>> Cadena::getSufijos() const {
  std::set<std::vector<Simbolo>> sufijos;
  sufijos.insert({CAD_VACIA});  // Insertar sufijo vacío
  for (size_t i = 0; i < cadena_.size(); i++) {
    std::vector<Simbolo> sufijo(cadena_.begin() + i, cadena_.end());
    sufijos.insert(sufijo);
  }
  return sufijos;
}

// método de inversa de una cadena
// método de inversa de una cadena
std::vector<Simbolo> Cadena::inversa() const {
  std::vector<Simbolo> inversa;
  for (int i = cadena_.size() - 1; i >= 0; i--) {
    inversa.push_back(cadena_[i]);  // agregar símbolo en orden inverso
  }
  return inversa;
}


// método que calcula la longitud de una cadena
size_t Cadena::getLongitud() const {
  return cadena_.size();
}

// sobrecarga del operador< para el uso de simbolos en set
bool Cadena::operator<(const Cadena& otra) const {
  return cadena_ < otra.cadena_;
}

// Sobrecarga del operador<< para mostrar la cadena
std::ostream& operator<<(std::ostream& os, const Cadena& cadena) {
  for (const auto& simbolo : cadena.cadena_) {  // recorrer cada símbolo de la cadena
    os << simbolo.getSimbolo();
  }
  return os;
}