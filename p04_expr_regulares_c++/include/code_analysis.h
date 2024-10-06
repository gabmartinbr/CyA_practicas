#ifndef CODE_ANALYSIS
#define CODE_ANALYSIS

#include <string>
#include <fstream>
#include <iostream>
#include <regex>
#include "code_block.h"

/**
 * @brief clase encargada de leer, analizar y exportar el contenido del archivo de entrada
 * 
 */
class CodeAnalysis {
private:
  std::string input_file_;
  std::string output_file_;
  CodeBlock code_block_;

public:
  // constructor
  CodeAnalysis(const std::string& input_file, const std::string& output_file);

  // metodo que abrira el archivo de entrada, leerá su contenido y analizara su contenido
  void AnalizeFile(const std::string& input_file);
  // metodo para escribir en el archivo de salida el analisis realizado
  void ExportReport(const std::string& input_file,const std::string& output_file);
  // metodo para analizar cada linea del archivo de entrada
  void LineParser(const std::string& line, int line_counter);
};









#endif // CODE_ANALYSIS_H