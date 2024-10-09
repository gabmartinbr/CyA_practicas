#ifndef COMMENT_H
#define COMMENT_H

#include <string>
#include <iostream>

/**
 * @class Comment
 * @brief Representa un comentario en el código, que puede ser de una sola línea o multilínea.
 * 
 * La clase almacena información sobre el tipo de comentario, las líneas donde comienza y termina, 
 * el contenido del comentario y si es una descripción.
 */
class Comment {
private:
  int ini_line_;           ///< Línea de inicio del comentario.
  int end_line_;           ///< Línea de fin del comentario.
  std::string content_;    ///< Contenido del comentario.
  std::string type_;       ///< Tipo de comentario (e.g., "single-line" o "multi-line").
  bool is_description_ = false; ///< Indica si el comentario es una descripción del bloque de código.

public:
  /**
   * @brief Constructor por defecto de la clase Comment.
   */
  Comment();

  /**
   * @brief Constructor de un comentario multilínea.
   * 
   * @param ini_line Línea inicial del comentario.
   * @param end_line Línea final del comentario.
   * @param content Contenido del comentario.
   * @param type Tipo de comentario ("multi-line").
   */
  Comment(int ini_line, int end_line, const std::string& content, const std::string& type);

  /**
   * @brief Constructor de un comentario de una sola línea.
   * 
   * @param ini_line Línea donde empieza el comentario.
   * @param content Contenido del comentario.
   * @param type Tipo de comentario ("single-line").
   */
  Comment(int ini_line, const std::string& content, const std::string& type);

  // Getters

  /**
   * @brief Obtiene la línea inicial del comentario.
   * 
   * @return Número de la línea inicial.
   */
  int GetIniLine() const;

  /**
   * @brief Obtiene la línea final del comentario.
   * 
   * @return Número de la línea final.
   */
  int GetEndLine() const;

  /**
   * @brief Obtiene el contenido del comentario.
   * 
   * @return El contenido como una cadena de caracteres.
   */
  std::string GetContent() const;

  /**
   * @brief Obtiene el tipo de comentario.
   * 
   * @return El tipo de comentario (e.g., "single-line", "multi-line").
   */
  std::string GetType() const;

  /**
   * @brief Verifica si el comentario es una descripción del bloque de código.
   * 
   * @return `true` si es una descripción, `false` en caso contrario.
   */
  bool GetIsDescription() const;

  /**
   * @brief Establece el comentario como una descripción.
   */
  void SetIsDescription();
};

/**
 * @brief Sobrecarga del operador de inserción `<<` para imprimir el comentario.
 * 
 * @param os Flujo de salida.
 * @param comm Comentario a imprimir.
 * @return El flujo de salida con el contenido del comentario.
 */
std::ostream& operator<<(std::ostream& os, const Comment& comm);

#endif  // COMMENT_H
