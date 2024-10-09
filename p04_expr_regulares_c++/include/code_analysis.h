#ifndef CODE_ANALYSIS
#define CODE_ANALYSIS

#include <string>
#include <fstream>
#include <iostream>
#include <regex>
#include <filesystem>
#include "code_block.h"

/**
 * @class CodeAnalysis
 * @brief Esta clase se encarga de realizar el análisis de código fuente, procesar cada línea del archivo de entrada
 * y generar un reporte con los resultados.
 */
class CodeAnalysis {
private:
  std::string input_file_;    ///< Nombre del archivo de entrada.
  std::string output_file_;   ///< Nombre del archivo de salida donde se genera el reporte.
  CodeBlock code_block_;      ///< Objeto que representa el bloque de código analizado.

public:
  /**
   * @brief Constructor de la clase CodeAnalysis.
   * 
   * @param input_file Nombre del archivo de entrada que se va a analizar.
   * @param output_file Nombre del archivo de salida donde se escribirá el reporte.
   */
  CodeAnalysis(const std::string& input_file, const std::string& output_file);

  /**
   * @brief Método que analiza el archivo de entrada línea por línea.
   * 
   * @param input_file Nombre del archivo de entrada que contiene el código a analizar.
   */
  void AnalizeFile(const std::string& input_file);

  /**
   * @brief Método que exporta el reporte del análisis al archivo de salida.
   * 
   * @param input_file Nombre del archivo de entrada.
   * @param output_file Nombre del archivo de salida donde se generará el reporte.
   */
  void ExportReport(const std::string& input_file, const std::string& output_file);

  /**
   * @brief Método que analiza cada línea del archivo de entrada.
   * 
   * Este método se encarga de procesar cada línea del archivo de código fuente, buscando comentarios,
   * bucles, variables y la función principal.
   * 
   * @param line Línea actual del archivo de código fuente.
   * @param line_counter Número de línea actual (contador).
   */
  void LineParser(const std::string& line, int line_counter);
};

#endif // CODE_ANALYSIS_H
