#ifndef VARIABLE_H
#define VARIABLE_H

#include <iostream>
#include <string>
#include <regex>

/**
 * @class Variable
 * @brief Representa una variable en el código, incluyendo su nombre, tipo, valor y la línea donde se declara.
 * 
 * La clase almacena la información sobre las variables detectadas en el código.
 */
class Variable {
private:
  std::string name_;        ///< Nombre de la variable.
  std::string type_;        ///< Tipo de la variable (e.g., int, double).
  std::string value_;       ///< Valor de la variable si está inicializada.
  int line_number_;         ///< Número de línea donde se declara la variable.
  bool is_asign_;

public:
  /**
   * @brief Constructor de la clase Variable.
   * 
   * @param line_counter Número de la línea donde se detecta la variable.
   * @param match Resultado de la expresión regular que detecta la variable.
   */
  Variable(int line_counter, std::smatch& match);


  bool GetAsign();
  void SetAsign();
  // Getters

  /**
   * @brief Obtiene el nombre de la variable.
   * 
   * @return El nombre de la variable como cadena de caracteres.
   */
  std::string GetName() const;

  /**
   * @brief Obtiene el tipo de la variable (e.g., int, double).
   * 
   * @return El tipo de la variable como cadena de caracteres.
   */
  std::string GetType() const;

  /**
   * @brief Obtiene el valor de la variable si está inicializada.
   * 
   * @return El valor de la variable como cadena de caracteres.
   */
  std::string GetValue() const;

  /**
   * @brief Obtiene el número de línea donde se declara la variable.
   * 
   * @return El número de línea.
   */
  int GetLineNumber() const;

  /**
   * @brief Convierte la información de la variable a un formato de cadena.
   * 
   * @return Una cadena que representa la información de la variable.
   */
  std::string ToString() const;
};

/**
 * @brief Sobrecarga del operador de inserción `<<` para imprimir información sobre la variable.
 * 
 * Imprime en el formato: `[ Line linenum ] type : name`
 * 
 * @param os Flujo de salida.
 * @param var Objeto de tipo Variable a imprimir.
 * @return El flujo de salida con la información de la variable.
 */
std::ostream& operator<<(std::ostream& os, const Variable& var);

#endif  // VARIABLE_H
