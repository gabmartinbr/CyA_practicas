#ifndef ALFABETO_H
#define ALFABETO_H

#include <set>
#include <string>
#include <stdexcept>  // Para std::invalid_argument
#include <iostream>
#include "simbolo.h"

/**
 * @brief Clase que representa un conjunto de símbolos, formando un alfabeto.
 */
class Alfabeto {
private:
  std::set<Simbolo> simbolos_;  ///< Conjunto de símbolos del alfabeto.

public:
  /**
   * @brief Constructor por defecto de la clase Alfabeto.
   */
  Alfabeto();

  /**
   * @brief Constructor de la clase Alfabeto a partir de un conjunto de símbolos.
   * 
   * @param simbolos Conjunto de símbolos que se añadirán al alfabeto.
   */
  Alfabeto(const std::set<Simbolo>& simbolos);

  /**
   * @brief Constructor de la clase Alfabeto a partir de una cadena de caracteres.
   * 
   * @param cadenaAlfabeto Cadena que contiene los caracteres que se convertirán en símbolos.
   */
  Alfabeto(const std::string& cadenaAlfabeto);

  /**
   * @brief Obtiene el conjunto de símbolos del alfabeto.
   * 
   * @return const std::set<Simbolo>& Referencia constante al conjunto de símbolos.
   */
  const std::set<Simbolo>& getSimbolos() const;

  /**
   * @brief Agrega un nuevo símbolo al conjunto de símbolos del alfabeto.
   * 
   * @param simbolo El símbolo que se añadirá al alfabeto.
   * @throw std::invalid_argument Si el símbolo es vacío ('\0').
   */
  void addSimbolo(const Simbolo& simbolo);

  /**
   * @brief Comprueba si un símbolo está incluido en el alfabeto.
   * 
   * @param simbolo El símbolo a comprobar.
   * @return true Si el símbolo está en el alfabeto.
   * @return false Si el símbolo no está en el alfabeto.
   */
  bool hasSimbolo(const Simbolo& simbolo) const;

  auto begin() const { return simbolos_.begin(); }
  auto end() const { return simbolos_.end(); }
  /**
   * @brief Sobrecarga del operador de salida para mostrar el alfabeto.
   * 
   * @param os Flujo de salida.
   * @param alfabeto Objeto Alfabeto a mostrar.
   * @return std::ostream& Referencia al flujo de salida.
   */
  friend std::ostream& operator<<(std::ostream& os, const Alfabeto& alfabeto);
};

#endif  // ALFABETO_H
