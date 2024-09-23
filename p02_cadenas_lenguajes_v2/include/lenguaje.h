#ifndef LENGUAJE_H
#define LENGUAJE_H

#include "cadena.h"
#include <iostream>

class Lenguaje {
private:
  std::set<Cadena> cadenas_;  ///< Conjunto de cadenas que forman el lenguaje.

public:
  /**
   * @brief Constructor por defecto de la clase Lenguaje.
   */
  Lenguaje();

  /**
   * @brief Constructor de la clase Lenguaje a partir de un conjunto de cadenas.
   * 
   * @param cadenas Conjunto de cadenas que conforman el lenguaje.
   */
  Lenguaje(const std::set<Cadena>& cadenas);

  /**
   * @brief Getter para obtener el conjunto de cadenas del lenguaje.
   * 
   * @return const std::set<Cadena>& Referencia constante al conjunto de cadenas.
   */
  const std::set<Cadena>& getCadenas() const;

  /**
   * @brief Método para añadir una nueva cadena al lenguaje.
   * 
   * @param cadena La cadena a añadir al conjunto.
   */
  void addCadena(const Cadena& cadena);

  /**
   * @brief Método para comprobar si una cadena ya está en el lenguaje.
   * 
   * @param cadena La cadena a comprobar.
   * @return true Si la cadena está en el lenguaje.
   * @return false Si la cadena no está en el lenguaje.
   */
  bool hasCadena(const Cadena& cadena) const;

  /**
   * @brief Sobrecarga del operador << para mostrar el lenguaje de forma legible.
   * 
   * @param os Flujo de salida.
   * @param lenguaje Objeto Lenguaje a mostrar.
   * @return std::ostream& Referencia al flujo de salida.
   */
  friend std::ostream& operator<<(std::ostream& os, const Lenguaje& lenguaje);
};

#endif  // LENGUAJE_H
