#ifndef CODE_BLOCK
#define CODE_BLOCK

#include <vector>
#include "comment.h"
#include "loop.h"
#include "variable.h"

/**
 * @class CodeBlock
 * @brief Representa un bloque de código que contiene comentarios, bucles, variables y una descripción opcional.
 * 
 * Esta clase gestiona los comentarios (single-line y multi-line), bucles, variables y si el código contiene 
 * una función `main`. También se puede almacenar una descripción del bloque de código.
 */
class CodeBlock {
private:
  std::vector<Comment> comments_;   ///< Vector que almacena los comentarios encontrados en el código.
  std::vector<Loop> loops_;         ///< Vector que almacena los bucles (for, while) encontrados.
  std::vector<Variable> variables_; ///< Vector que almacena las variables encontradas en el código.
  Comment description_;             ///< Comentario que representa la descripción del bloque de código.
  bool has_description_;            ///< Indica si el bloque tiene una descripción.
  bool has_main_func_;              ///< Indica si el código contiene una función main.

public:
  /**
   * @brief Constructor de la clase CodeBlock.
   */
  CodeBlock();

  /**
   * @brief Añade un comentario al bloque de código.
   * 
   * @param comment Comentario que se va a añadir.
   */
  void AddComment(const Comment& comment);

  /**
   * @brief Añade un bucle (loop) al bloque de código.
   * 
   * @param loop Bucle que se va a añadir.
   */
  void AddLoop(const Loop& loop);

  /**
   * @brief Añade una variable al bloque de código.
   * 
   * @param variable Variable que se va a añadir.
   */
  void AddVariable(const Variable& variable);

  /**
   * @brief Establece si el bloque de código contiene una función `main`.
   * 
   * @param has_main Booleano que indica si el bloque contiene o no una función `main`.
   */
  void SetHasMain(bool has_main);

  /**
   * @brief Establece la descripción del bloque de código.
   * 
   * @param comm Comentario que se va a usar como descripción.
   */
  void SetDescription(const Comment& comm);

  /**
   * @brief Obtiene los comentarios del bloque de código.
   * 
   * @return Un vector constante que contiene los comentarios.
   */
  const std::vector<Comment>& GetComments() const;

  /**
   * @brief Obtiene las variables encontradas en el bloque de código.
   * 
   * @return Un vector constante que contiene las variables.
   */
  const std::vector<Variable>& GetVariables() const;

  /**
   * @brief Obtiene los bucles (loops) encontrados en el bloque de código.
   * 
   * @return Un vector constante que contiene los bucles.
   */
  const std::vector<Loop>& GetLoops() const;

  /**
   * @brief Verifica si el bloque de código contiene una función `main`.
   * 
   * @return `true` si el bloque contiene una función `main`, `false` en caso contrario.
   */
  bool HasMain() const;

  /**
   * @brief Verifica si el bloque de código tiene una descripción.
   * 
   * @return `true` si el bloque tiene una descripción, `false` en caso contrario.
   */
  bool HasDescription() const;

  /**
   * @brief Obtiene la descripción del bloque de código.
   * 
   * @return Un comentario que representa la descripción.
   */
  const Comment& GetDescription() const;

};

#endif  // CODE_BLOCK_H
