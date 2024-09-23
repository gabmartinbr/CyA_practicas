// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 2: Cadenas y lenguajes
// Autor: Gabriel Martín Broock
// Correo: alu0101539157@ull.edu.es
// Fecha: 22/09/2024
// Archivo simbolo.h: clase simbolo.
// Contiene la declaración de la clase simbolo 
// para poder usar objetos tipo símbolos para la creación de cadenas
// Referencias:
// Enlaces de interés /
// Historial de revisiones:
// 19/09/2024 - Creación (primera versión) del código

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
  /**
   * @brief Constructor de la clase Simbolo.
   * 
   * @param simbolo Carácter que representa el símbolo.
   */
  Simbolo(char simbolo);

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
   * @brief Sobrecarga del operador << para imprimir símbolos.
   * 
   * @param os Flujo de salida.
   * @param simbolo Objeto Simbolo a imprimir.
   * @return std::ostream& Referencia al flujo de salida.
   */
  friend std::ostream& operator<<(std::ostream& os, const Simbolo& simbolo);
};

#endif  // SIMBOLO_H
