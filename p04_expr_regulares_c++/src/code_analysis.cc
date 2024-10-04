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
  std::regex inline_comments_regex("\/\/(.*)"); // podrá ser + y no tener un comentario vacio ?

  static bool is_multiline_comment = false;
  std::regex ini_multiline_comments_regex(R"(\/\*(.*))");
  std::regex end_multiline_comments_regex(R"(^\*\/$)");

  std::regex int_variables_regex(R"(^\s*int\s\w+(;|\{\d+\};|\s=\s\d+;|\{\};))");
  std::regex double_variables_regex(R"(^\s*double\s\w+(;|\{\d+\.\d+\};|\{\d+\};|\s=\s\d+;|\s=\s\d+\.\d+;)");

  std::regex for_loops_regex(R"(^\bfor\s\(.*\)\s\{$)");
  std::regex while_loops_regex(R"(^\bwhile\s\(.*\)\s\{$)");

  std::regex has_main(R"(^int\smain\(.*\)\s\{?)");

  // detectar comentarios inline
  if (std::regex_search(line, matches, inline_comments_regex)) {
    Comment comment(line_counter, line_counter, matches[1].str(), "inline");  // creación de objeto Comentario
    comments_.pushback(comment);  // pushback a vector de comentarios de CodeBlock
    return;
  }

  // detectar comentarios multilínea
  if(is_multiline_comment) {
    if (std::regex_search(line, matches, end_multiline_comments_regex)) {
      Comment comment()
    }
  }

  
}

//loops
