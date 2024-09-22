// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 2: Cadenas y lenguajes
// Autor: Gabriel Martín Broock
// Correo: alu0101539157@ull.edu.es
// Fecha: 22/09/2024
// Archivo alfabeto.cc: clase alfabeto.
// Contiene la implementación de la clase alfabeto 
// para poder usar objetos tipo alfabeto(set de simbolos) y 
// realizar operaciones a las mismas
// Referencias:
// Enlaces de interés /
// Historial de revisiones:
// 19/09/2024 - Creación (primera versión) del código
#include "alfabeto.h"

// constructor
Alfabeto::Alfabeto() {}

Alfabeto::Alfabeto(const std::set<Simbolo>& simbolos) { 
  for (const auto& simbolo : simbolos) {
    addSimbolo(simbolo);  // añadir simbolo al set de simbolos
  }
}

// getter de conjunto de símbolos
const std::set<Simbolo>& Alfabeto::getSimbolos() const {
  return simbolos_;
}

// método para agregar un nuevo símbolo al set 
void Alfabeto::addSimbolo(const Simbolo& simbolo) {
  if (simbolo.getSimbolo() != '\0') {
    simbolos_.insert(simbolo);
  } else {
    throw std::invalid_argument("El símbolo no puede ser vacío para añadirse al alfabeto");
  }
}

// método para comprobar si ya está incluido un símbolo
bool Alfabeto::hasSimbolo(const Simbolo& simbolo) const{
  return simbolos_.find(simbolo) != simbolos_.end(); // retorna true si el final del set no es el simbolo
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