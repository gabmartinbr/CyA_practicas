#ifndef SIMBOLO_H
#define SIMBOLO_H   

#include <iostream>

/**
 * @class Simbolo
 * @brief Clase para representar un símbolo a partir de un carácter.
 */
class Simbolo {
private:
  char simbolo_; ///< Carácter que representa el símbolo.

public:
  std::string value;
  /**
   * @brief Constructor de la clase Simbolo.
   * 
   * @param simbolo Carácter que representa el símbolo.
   */
  Simbolo(char simbolo);
  Simbolo(const std::string& val) : value(val) {}    
    // Default constructor
    Simbolo() : value("") {}


  /**
   * @brief Obtiene el símbolo como carácter.
   * 
   * @return char El símbolo almacenado.
   */
  char getSimbolo() const;

  /**
   * @brief Sobrecarga del operador < para comparar símbolos.
   * 
   * @param otro Otro objeto Simbolo a comparar.
   * @return true Si el símbolo actual es menor que el otro.
   * @return false En caso contrario.
   */
  bool operator<(const Simbolo& otro) const;

  /**
   * @brief Sobrecarga del operador == para comparar símbolos.
   * 
   * @param otro Otro objeto Simbolo a comparar.
   * @return true Si el símbolo actual es igual que el otro.
   * @return false En caso contrario.
   */
  bool operator==(const Simbolo& otro) const;

  // Sobrecarga del operador !=
  bool operator!=(const Simbolo& other) const;
  /**
   * @brief Sobrecarga del operador << para imprimir símbolos.
   * 
   * @param os Flujo de salida.
   * @param simbolo Objeto Simbolo a imprimir.
   * @return std::ostream& Referencia al flujo de salida.
   */
  friend std::ostream& operator<<(std::ostream& os, const Simbolo& simbolo);
};

#endif  // SIMBOLO_H
