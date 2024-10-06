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
  std::smatch matches;  //coincidencias con las regex 

  // regex comentarios
  std::regex inline_comments_regex("\/\/(.*)"); // podrá ser + y no tener un comentario vacio ?
  std::regex ini_multiline_comments_regex(R"(\/\*(.*))");
  std::regex end_multiline_comments_regex(R"(^\*\/$)");

  int start_multiline_comment = 0;  // linea de inicio del multilinea
  std::string multiline_comment_content;  // almacenar contenido de comentario linea por linea
  bool in_multiline_comment = false;  // flag para saber si es inline o no

  // Detectar si estamos en un comentario de múltiples líneas
  if (in_multiline_comment) {
      // Buscar el final del comentario multilínea
      if (std::regex_search(line, matches, end_multiline_comments_regex)) {
          // Añadir última línea de multilinea al contenido del comentario
          multiline_comment_content += line.substr(0, matches.position() + matches.length()) + "\n";

          // Crear objeto comentario
          Comment comment(start_multiline_comment, line_counter, multiline_comment_content, "multi-line");
          // Añadir comentario a vector de comentarios 
          code_block_.AddComment(comment);

          // Resetear variables
          in_multiline_comment = false;
          multiline_comment_content.clear();
      } else {
          // Si no se encuentra fin de comentario, se guarda la línea completa
          multiline_comment_content += line + "\n";
      }
  }
  // Detectar inicio de un comentario multilínea
  else if (std::regex_search(line, matches, ini_multiline_comments_regex)) {
      in_multiline_comment = true;
      start_multiline_comment = line_counter;

      // Almacenar la primera línea de comentario
      multiline_comment_content = line + "\n";
      return;
  }

  // Detectar si hay un comentario en línea
  if (std::regex_search(line, matches, inline_comments_regex)) {
      // Crear objeto comentario
      Comment comment(line_counter, line_counter, "single-line");
      
      // Añadir el comentario al vector de comentarios
      code_block_.AddComment(comment);
      return;
  }



  // regex bucles
  std::regex for_loops_regex(R"(^\bfor\s\(.*\)\s\{$)");
  std::regex while_loops_regex(R"(^\bwhile\s\(.*\)\s\{$)");

  // detectar for loops
  if (std::regex_search(line, matches, for_loops_regex)) {
    // crear objeto loop
    Loop loop(line_counter, matches.str());
    // añadir el for al vector de bucles
    code_block_.AddLoop(loop);
    return;
  }

  // detectar while loops
  if (std::regex_search(line, matches, while_loops_regex)) {
    // crear objeto loop
    Loop loop(line_counter, matches.str());
    // añadir el while al vector de bucles
    code_block_.AddLoop(loop);
    return;
  }

  //regex variables
  std::regex int_variables_regex(R"(^\s*int\s\w+(;|\{\d+\};|\s=\s\d+;|\{\};))");
  std::regex double_variables_regex(R"(^\s*double\s\w+(;|\{\d+\.\d+\};|\{\d+\};|\s=\s\d+;|\s=\s\d+\.\d+;)");

  // detectar enteros
  if (std::regex_search(line, matches, int_variables_regex)) {
    // crear objeto variable
    Variable var(line_counter, matches.str());
    return;
  }

  // detectar dobbles
  if (std::regex_search(line, matches, double_variables_regex)) {
    // crear objeto variable
    Variable var(line_counter, matches.str());
    return;
  }

  // detectar si hay funcion main
  std::regex has_main(R"(^\s*int\s+main\s*\(.*\)\s*\{)");

  if (std::regex_search(line, matches, has_main)) {
    code_block_.SetHasMain(true);
    return;
  }
}

void CodeAnalysis::ExportReport(const std::string& input_file,const std::string& output_file) {
  std::ofstream report_file(output_file);
  if(!report_file.is_open()) {
    std::cerr << "Error al abrir o crear el archivo de salida " << output_file << std::endl;
    return;
  }

  report_file << "PROGRAM: " << input_file << "\n";

  // imprimir descripcion
  bool has_description = false;
  for (const auto& comment : code_block_.GetComments()) {
    if (comment.GetType() == "multi-line" && comment.GetStartLine() == 1) {
      report_file << "DESCRIPTION \n";
      report_file << comment.GetContent() << "\n";
      has_description = true;
      break;
    }
  }

  if (!has_description) {
    report_file << "DESCRIPTION: \n";
    report_file << "No description found in file \n";
  }

  // imprimir variables
  report_file << "\nVARIABLES:\n";
  for (const auto& var : code_block_.GetVariables()) {
    report_file << var.ToString() << "\n";
  }

  // imprimir bucles
  report_file << "\nLOOPS:\n";
  for (const auto& loop : code_block_.GetLoops()) {
    report_file << loop.ToString() << "\n";
  }

  // imprimir si tiene main
  if (code_block_.HasMain()) {
    report_file << "\nMAIN: \nTrue\n";
  }

  // imprimir comentarios de ambos tipos
  report_file << "\nCOMMENTS :\n";
    for (const auto& comment : code_block_.GetComments()) {
      // Saltar el comentario que ya hemos usado como descripción
      if (comment.GetType() == "multi-line" && comment.GetStartLine() <= 2) {
        continue;
      }
      
      // Verificar si es un comentario inline o multi-line
      if (comment.GetType() == "single-line") {
        // Imprimir comentarios de una sola línea
        report_file << "[ Line " << comment.GetStartLine() << "] " << "// " << comment.GetContent() << "\n";
      } else if (comment.GetType() == "multi-line") {
        // Imprimir comentarios multilinea
        report_file << "[ Line " << comment.GetStartLine() << " - " << comment.GetEndLine() << "] " << "/* " << comment.GetContent() << " */" << "\n";
      }
    }  
  report_file.close();
}