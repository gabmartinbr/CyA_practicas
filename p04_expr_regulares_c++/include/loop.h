#ifndef LOOP_H
#define LOOP_H

#include <string>
#include <iostream>
#include <regex>

/**
 * @class Loop
 * @brief Representa un bucle en el código (e.g., bucles `for` o `while`).
 * 
 * La clase almacena información sobre la línea en la que aparece el bucle y su tipo.
 */
class Loop {
private:
  int line_number_;   ///< Número de la línea donde aparece el bucle.
  std::string type_;  ///< Tipo de bucle (e.g., "for", "while").

public:
  /**
   * @brief Constructor de la clase Loop.
   * 
   * @param line_counter Número de la línea donde se detecta el bucle.
   * @param match Resultado de la expresión regular que detecta el bucle.
   */
  Loop(int line_counter, std::smatch& match);

  // Getters

  /**
   * @brief Obtiene el número de línea donde se encuentra el bucle.
   * 
   * @return Número de la línea.
   */
  int GetLineNumber() const;

  /**
   * @brief Obtiene el tipo de bucle (e.g., "for", "while").
   * 
   * @return Tipo de bucle como cadena de caracteres.
   */
  std::string GetType() const;
};

/**
 * @brief Sobrecarga del operador de inserción `<<` para imprimir información sobre el bucle.
 * 
 * @param os Flujo de salida.
 * @param loop Objeto de tipo Loop a imprimir.
 * @return El flujo de salida con la información del bucle.
 */
std::ostream& operator<<(std::ostream& os, const Loop& loop);

#endif  // LOOP_H
