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
  ExportReport(input_file, output_file_);
}

void CodeAnalysis::LineParser(const std::string& line, int line_counter) {
    std::smatch matches;  // coincidencias con las regex 

    try {
        // regex comentarios
        std::regex inline_comments_regex(R"(//(.*))"); // Comentarios en línea
        std::regex ini_multiline_comments_regex(R"(\/\*(.*))"); // Inicio de comentarios multilínea
        std::regex end_multiline_comments_regex(R"(^\*\/$)"); // Fin de comentarios multilínea

        int start_multiline_comment = 0;  // línea de inicio del comentario
        std::string multiline_comment_content;  // almacenar contenido de comentario línea por línea
        bool in_multiline_comment = false;  // flag para saber si es inline o no

        // Detectar si estamos en un comentario de múltiples líneas
        if (in_multiline_comment) {
            // Buscar el final del comentario multilínea
            if (std::regex_search(line, matches, end_multiline_comments_regex)) {
                // Añadir última línea de multilínea al contenido del comentario
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

        // Comprobar si hay un comentario multilínea al principio del archivo
        if (line_counter == 1 && in_multiline_comment) {
            // Añadir el comentario como descripción
            Comment description_comment(1, line_counter, multiline_comment_content, "description");
            code_block_.AddComment(description_comment);
            multiline_comment_content.clear();  // Limpiar contenido de descripción
            return;  // Salir de la función, ya que la descripción se maneja
        }

        // Detectar si hay un comentario en línea
        if (std::regex_search(line, matches, inline_comments_regex)) {
            // Crear objeto comentario
            Comment comment(line_counter, matches[1].str(), "single-line");
            
            // Añadir el comentario al vector de comentarios
            code_block_.AddComment(comment);
            return;
        }

        // regex bucles
        std::regex for_loops_regex(R"(^\s*(for)\s*\(.*\)\s*\{)"); // Bucles for
        std::regex while_loops_regex(R"(^\s*(while)\s*\(.*\)\s*\{)"); // Bucles while

        // detectar for loops
        if (std::regex_search(line, matches, for_loops_regex)) {
            // crear objeto loop
            Loop loop(line_counter, matches);
            // añadir el for al vector de bucles
            code_block_.AddLoop(loop);
            return;
        }

        // detectar while loops
        if (std::regex_search(line, matches, while_loops_regex)) {
            // crear objeto loop
            Loop loop(line_counter, matches);
            // añadir el while al vector de bucles
            code_block_.AddLoop(loop);
            return;
        }

        // regex variables
        std::regex int_variables_regex(R"(^\s*(int)\s+(\w+)(\s*=\s*\d+)?\s*;|\s*\{(\d+)\}\s*;)");
        std::regex double_variables_regex(R"(^\s*(double)\s+(\w+)(\s*=\s*\d+\.\d+)?\s*;|\s*\{(\d+)\}\s*;)");

        // detectar enteros
        if (std::regex_search(line, matches, int_variables_regex)) {
            // crear objeto variable
            Variable var(line_counter, matches);
            code_block_.AddVariable(var);
            return;
        }

        // detectar doubles
        if (std::regex_search(line, matches, double_variables_regex)) {
            // crear objeto variable
            Variable var(line_counter, matches);
            code_block_.AddVariable(var);
            return;
        }

        // detectar si hay función main
        std::regex has_main(R"(^\s*int\s+main\s*\(.*\)\s*\{)"); // Función main

        if (std::regex_search(line, matches, has_main)) {
            code_block_.SetHasMain(true);
            return;
        }
    } catch (const std::regex_error& e) {
        std::cerr << "Regex error in line " << line_counter << ": " << e.what() << std::endl;
        // Aquí puedes manejar el error de acuerdo a tus necesidades (por ejemplo, omitir la línea o detener el análisis)
    }
}




void CodeAnalysis::ExportReport(const std::string& input_file, const std::string& output_file) {
  std::ofstream report_file(output_file);
  if (!report_file.is_open()) {
    std::cerr << "Error al abrir o crear el archivo de salida " << output_file << std::endl;
    return;
  }

  report_file << "PROGRAM: " << input_file << "\n\n";

  // Imprimir descripción
  bool has_description = false;
  for (const auto& comment : code_block_.GetComments()) {
    if (comment.GetType() == "multi-line" && comment.GetIniLine() == 1) {
      report_file << "DESCRIPTION:\n";
      report_file << comment.GetContent() << "\n";
      has_description = true;
      break;
    }
  }

  if (!has_description) {
    report_file << "DESCRIPTION:\n";
    report_file << "No description found in file\n";
  }

  report_file << "\nVARIABLES:\n";
  for (const auto& var : code_block_.GetVariables()) {
    report_file << var << "\n";
    report_file << "prueba\n";
  }


  report_file << "\nSTATEMENTS:\n";
  for (const auto& loop : code_block_.GetLoops()) {
    report_file << loop << "\n";
  }

  // Imprimir si tiene main
  report_file << "\nMAIN:\n";
  if (code_block_.HasMain()) {
    report_file << "True\n";
  } else {
    report_file << "False\n"; // Si quieres indicar que no hay main
  }

  // Imprimir comentarios de ambos tipos
  report_file << "\nCOMMENTS:\n";
  for (const auto& comment : code_block_.GetComments()) {
    // Saltar el comentario que ya hemos usado como descripción
    if (comment.GetType() == "multi-line" && comment.GetIniLine() == 1) {
      continue;
    }

    // Verificar si es un comentario inline o multi-line
    if (comment.GetType() == "single-line") {
      // Imprimir comentarios de una sola línea
      report_file << "[ Line " << comment.GetIniLine() << "] " << "// " << comment.GetContent() << "\n";
    } else if (comment.GetType() == "multi-line") {
      // Imprimir comentarios multilínea
      report_file << "[ Line " << comment.GetIniLine() << " - " << comment.GetEndLine() << "] " << "DESCRIPTION\n";
    } 
  }
  report_file.close();
}