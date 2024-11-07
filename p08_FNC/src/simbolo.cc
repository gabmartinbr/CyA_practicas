#include "simbolo.h"
#include <stdexcept>  // Para std::invalid_argument

/**
 * @brief Constructor de la clase Simbolo.
 * 
 * @param simbolo Carácter que representa el símbolo.
 * @throw std::invalid_argument Si el símbolo es un carácter nulo.
 */
Simbolo::Simbolo(char simbolo) {
  if (simbolo == '\0') {
    throw std::invalid_argument("No pueden haber símbolos nulos.");
  }
  simbolo_ = simbolo;
}

/**
 * @brief Obtiene el símbolo como carácter.
 * 
 * @return char El símbolo almacenado.
 */
char Simbolo::getSimbolo() const {
  return simbolo_;
}

/**
 * @brief Sobrecarga del operador < para comparar símbolos.
 * 
 * @param otro Otro objeto Simbolo a comparar.
 * @return true Si el símbolo actual es menor que el otro.
 * @return false En caso contrario.
 */
bool Simbolo::operator<(const Simbolo& otro) const {
  return simbolo_ < otro.getSimbolo();
}

/**
 * @brief Sobrecarga del operador == para comparar símbolos.
 * 
 * @param otro Otro objeto Simbolo a comparar.
 * @return true Si el símbolo actual es igual que el otro.
 * @return false En caso contrario.
 */
bool Simbolo::operator==(const Simbolo& otro) const {
  return simbolo_ == otro.simbolo_;
}

bool Simbolo::operator!=(const Simbolo& otro) const {
  return simbolo_ != otro.simbolo_;
}

/**
 * @brief Sobrecarga del operador << para imprimir símbolos.
 * 
 * @param os Flujo de salida.
 * @param simbolo Objeto Simbolo a imprimir.
 * @return std::ostream& Referencia al flujo de salida.
 */
std::ostream& operator<<(std::ostream& os, const Simbolo& simbolo) {
  os << simbolo.getSimbolo();
  return os;
}
