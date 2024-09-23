// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 2: Cadenas y lenguajes
// Autor: Gabriel Martín Broock
// Correo: alu0101539157@ull.edu.es
// Fecha: 22/09/2024
// Archivo cadena.cc: clase cadena.
// Contiene la declaración de la clase cadena 
// para poder usar objetos tipo cadena(vector de simbolos) y 
// realizar operaciones a las mismas
// Referencias:
// Enlaces de interés /
// Historial de revisiones:
// 19/09/2024 - Creación (primera versión) del código

#include "cadena.h"

// definición de cadena vacía
const Simbolo Cadena::CAD_VACIA = Simbolo('&');

// constructor para formar cadena a partir de un vector de simbolos
Cadena::Cadena() {}

Cadena::Cadena(const std::vector<Simbolo>& simbolos, const Alfabeto& alfabeto)
  : cadena_(simbolos), alfabeto_(alfabeto) {

  }
// getter para obtener la cadena
const std::vector<Simbolo>& Cadena::getCadena() const {
  return cadena_;
}
// getter para obtener el alfabeto de dicha cadena
const Alfabeto& Cadena::getAlfabeto() const {
  return alfabeto_;
}

// método para añadir simbolos a una cadena
void Cadena::addSimbolo(const Simbolo& simbolo) {
  cadena_.push_back(simbolo);
}

// método para obtener sufijos de la forma abc -> {&,a,ab,abc} con la sobrecarga << de lenguaje
std::set<Cadena> Cadena::getPrefijos() const {
  std::set<Cadena> prefijos;  // conjunto de prefijos
  Cadena simbolosPrefijo; // almacenar cada símbolo de cada prefijo
  
  // Añadir la cadena vacía como primer prefijo
  prefijos.insert(Cadena());  // insertar la cadena vacía (&)

  for (size_t i = 0; i < cadena_.size(); i++) { // recorrer cadena desde el principio
    simbolosPrefijo.addSimbolo(cadena_[i]); // añadir símbolo a la cadena de prefijo
    prefijos.insert(simbolosPrefijo); // añadir cadena prefijos al conjunto prefijos
  }

  return prefijos;
}
// método para obtener prefijos de la forma abc -> {&,a,ab,abc} con la sobrecarga << de lenguaje
std::set<Cadena> Cadena::getSufijos() const {
    std::set<Cadena> sufijos; // conjunto de sufijos
    sufijos.insert(Cadena()); // añadir el sufijo vacío (&)

    // Crear sufijos comenzando desde cada posición
    for (size_t i = 0; i < cadena_.size(); i++) {
        Cadena sufijo;  // sufijo temporal
        // Agregar los símbolos desde la posición actual hasta el final
        for (size_t j = i; j < cadena_.size(); j++) {
            sufijo.addSimbolo(cadena_[j]); // añadir símbolo al sufijo
        }
        sufijos.insert(sufijo); // añadir sufijo al conjunto
    }

    return sufijos;
}


// método que devuelve la cadena inversa 
Cadena Cadena::getInversa() const {
  std::vector<Simbolo> simbolosInversa; // vector de simbolos para construir cadena inversa
  for (int i = cadena_.size() - 1; i >= 0; i--) { // recorrer cadena desde el final
    simbolosInversa.push_back(cadena_[i]);  // agregar símbolo en orden inverso al vector de simbolos
  }
  Cadena inversa(simbolosInversa, getAlfabeto());  // crear cadena inversa y consecuentemente su alfabeto
  return inversa;
}


// método que devuelve la longitud, numero de simbolos, de una cadena
size_t Cadena::getLongitud() const {
  return cadena_.size();
}

// sobrecarga del operador< para el uso de cadenas ordenadas con set
bool Cadena::operator<(const Cadena& otra) const {
    if (cadena_.size() < otra.cadena_.size()) {
      return true;
    } else if (cadena_.size() > otra.cadena_.size()) {
      return false;
    }
    for (size_t i = 0; i < cadena_.size(); i++) {
      if (cadena_[i].getSimbolo() < otra.cadena_[i].getSimbolo()) {
        return true;
      } else if (cadena_[i].getSimbolo() > otra.cadena_[i].getSimbolo()) {
        return false;
      }
    }
    return false;
}

// Sobrecarga del operador<< para mostrar la cadena de forma abc...
std::ostream& operator<<(std::ostream& os, const Cadena& cadena) {
  for (const auto& simbolo : cadena.cadena_) {  // recorrer cada símbolo de la cadena
    os << simbolo.getSimbolo();
  }
  return os;
}