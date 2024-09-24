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

/**
 * @brief Constructor por defecto de la clase Alfabeto.
 */
Alfabeto::Alfabeto() {}

/**
 * @brief Constructor de la clase Alfabeto a partir de un conjunto de símbolos.
 * 
 * @param simbolos Conjunto de símbolos que se añadirán al alfabeto.
 */
Alfabeto::Alfabeto(const std::set<Simbolo>& simbolos) { 
  for (const auto& simbolo : simbolos) {
    addSimbolo(simbolo);  // añadir simbolo al set de simbolos
  }
}

/**
 * @brief Constructor de la clase Alfabeto a partir de una cadena de caracteres.
 * 
 * @param stringAlfabeto Cadena que contiene los caracteres que se convertirán en símbolos.
 */
Alfabeto::Alfabeto(const std::string& stringAlfabeto) {
  // Recorrer cada carácter del string y convertirlo en un objeto Simbolo
  for (char c : stringAlfabeto) {
    Simbolo simbolo(c);  // Crear un objeto Simbolo desde el carácter
    addSimbolo(simbolo);  // Añadir el símbolo al set de símbolos
  }
}

/**
 * @brief Obtiene el conjunto de símbolos del alfabeto.
 * 
 * @return const std::set<Simbolo>& Referencia constante al conjunto de símbolos.
 */
const std::set<Simbolo>& Alfabeto::getSimbolos() const {
  return simbolos_;
}

/**
 * @brief Agrega un nuevo símbolo al conjunto de símbolos del alfabeto.
 * 
 * @param simbolo El símbolo que se añadirá al alfabeto.
 * @throw std::invalid_argument Si el símbolo es vacío ('\0').
 */
void Alfabeto::addSimbolo(const Simbolo& simbolo) {
  if (simbolo.getSimbolo() != '\0') {
    simbolos_.insert(simbolo);
  } else {
    throw std::invalid_argument("El símbolo no puede ser vacío para añadirse al alfabeto");
  }
}

/**
 * @brief Comprueba si un símbolo está incluido en el alfabeto.
 * 
 * @param simbolo El símbolo a comprobar.
 * @return true Si el símbolo está en el alfabeto.
 * @return false Si el símbolo no está en el alfabeto.
 */
bool Alfabeto::hasSimbolo(const Simbolo& simbolo) const {
  return simbolos_.find(simbolo) != simbolos_.end(); // retorna true si el final del set no es el simbolo
}

/**
 * @brief Sobrecarga del operador de salida para mostrar el alfabeto.
 * 
 * @param os Flujo de salida.
 * @param alfabeto Objeto Alfabeto a mostrar.
 * @return std::ostream& Referencia al flujo de salida.
 */
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
