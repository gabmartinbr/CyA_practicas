#ifndef PRODUCTION_H
#define PRODUCTION_H

#include "cadena.h"
#include "simbolo.h"

class Production {
private:
  Simbolo noTerminal_; ///< simbolo no terminal de una produccion (left side)
  Cadena production_;  ///< cadena de simbolos terminales y no terminales (right
                       ///< side)

public:
  /**
   * @brief Constructor de objeto produccion
   *
   * @param no_terminal
   * @param production
   */
  Production(const Simbolo &no_terminal, const Cadena &production);

  // getters
  /**
   * @brief getter de simbolo no terminal
   *
   * @return Simbolo
   */
  Simbolo getNoTerminal() const;

  /**
   * @brief getter de conjunto de simbolos terminales o no(produccion)
   *
   * @return Cadena
   */
  Cadena getProduction() const;

  // comprobaciones
  /**
   * @brief comprobacion de si la produccion es vacia
   *
   * @return true
   * @return false
   */
  bool isEmptyProd() const;

  /**
   * @brief comprobacion de si la produccion es unitaria
   *
   * @return true
   * @return false
   */
  bool isUnitProd() const;
};

/**
 * @brief sobrecarga del operador << para imprimir una produccion
 *
 * @param os
 * @param production
 * @return std::ostream&
 */
std::ostream &operator<<(std::ostream &os, const Production &production);

#endif // PRODUCTION_H
