#include "code_analysis.h"

CodeAnalysis::CodeAnalysis(const std::string& input_file, const std::string& output_file) :
  input_file_{input_file}, output_file_{output_file} {}

void CodeAnalysis::AnalizeFile(const std::string& input_file) {
  std::ifstream file(input_file);
  if (!file.is_open()) {
    std::cerr << "Error al abrir archivo de entrada" << std::endl;
    return;
  }

  // crear linea para leer el archivo y contador de línea
  std::string line;
  int line_counter = 1;

  // mientras que hayan lineas por leer, analizar linea
  while (std::getline(file, line)) {
    LineParser(line, line_counter++);
  }

  // cerrar archivo de entrada y generar reporte del analisis
  file.close();
  ExportReport();
}

void CodeAnalysis::LineParser(const std::string& line, int line_counter) {
  std::smatch matches;

  // regex a analizar
  std::regex inline_comments_regex();
  std::regex multiline_comments_regex();
  std::regex variables_regex();
  std::regex loops_regex();

}