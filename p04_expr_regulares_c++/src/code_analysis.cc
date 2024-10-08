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
        // Expresiones regulares para comentarios
        std::regex inline_comments_regex(R"(//(.*))");  // Comentarios en línea
        std::regex ini_multiline_comments_regex(R"(\/\*)"); // Inicio de comentarios multilínea
        std::regex end_multiline_comments_regex(R"(\*\/)"); // Fin de comentarios multilínea

        // Variables para manejar comentarios multilínea
        static int start_multiline_comment = 0;
        static std::string multiline_comment_content;
        static bool in_multiline_comment = false;

        // Si ya estamos dentro de un comentario multilínea
        if (in_multiline_comment) {
            if (std::regex_search(line, matches, end_multiline_comments_regex)) {
                // Encontramos el fin del comentario multilínea
                multiline_comment_content += line.substr(0, matches.position() + matches.length()) + "\n";

                // Crear comentario multilínea
                if (start_multiline_comment == 1) {
                    // Guardar como descripción si inicia en la línea 1
                    Comment description_comment(1, line_counter, multiline_comment_content, "description");
                    description_comment.SetIsDescription();
                    code_block_.AddComment(description_comment);
                } else {
                    // Comentario multilínea normal
                    Comment comment(start_multiline_comment, line_counter, multiline_comment_content, "multi-line");
                    code_block_.AddComment(comment);
                }

                // Reiniciar el estado
                in_multiline_comment = false;
                multiline_comment_content.clear();
            } else {
                // Seguimos acumulando el comentario
                multiline_comment_content += line + "\n";
            }
            return;  // No proceses más si estamos en un comentario multilínea
        }

        // Detectar el inicio de un comentario multilínea
        if (std::regex_search(line, matches, ini_multiline_comments_regex)) {
            in_multiline_comment = true;
            start_multiline_comment = line_counter;
            multiline_comment_content = line + "\n";
            return;
        }

        // Comprobar si hay un comentario multilínea al principio del archivo (para la descripción)
        if (line_counter == 1 && !multiline_comment_content.empty()) {
            Comment description_comment(1, line_counter, multiline_comment_content, "description");
            description_comment.SetIsDescription();
            code_block_.AddComment(description_comment);
            multiline_comment_content.clear();  // Limpiar contenido de descripción
            return;
        }

        // Comentarios en línea
        if (std::regex_search(line, matches, inline_comments_regex)) {
            Comment comment(line_counter, matches[1].str(), "single-line");
            code_block_.AddComment(comment);
            return;
        }

        // Expresiones regulares para bucles
        std::regex for_loops_regex(R"(^\s*(for)\s*\(.*\)\s*\{)"); // Bucles for
        std::regex while_loops_regex(R"(^\s*(while)\s*\(.*\)\s*\{)"); // Bucles while

        // Detectar for loops
        if (std::regex_search(line, matches, for_loops_regex)) {
            Loop loop(line_counter, matches); // Añadir solo "for"
            code_block_.AddLoop(loop);
            return;
        }

        // Detectar while loops
        if (std::regex_search(line, matches, while_loops_regex)) {
            Loop loop(line_counter, matches); // Añadir solo "while"
            code_block_.AddLoop(loop);
            return;
        }

        // Expresiones regulares para variables
        std::regex int_variables_regex(R"(^\s*(int)\s+(\w+)(\s*=\s*\d+)?\s*;|\s*\{(\d+)\}\s*;)");
        std::regex double_variables_regex(R"(^\s*(double)\s+(\w+)(\s*=\s*\d+\.\d+)?\s*;|\s*\{(\d+)\}\s*;)");

        // Detectar enteros
        if (std::regex_search(line, matches, int_variables_regex)) {
            Variable var(line_counter, matches);
            code_block_.AddVariable(var);
            return;
        }

        // Detectar doubles
        if (std::regex_search(line, matches, double_variables_regex)) {
            Variable var(line_counter, matches);
            code_block_.AddVariable(var);
            return;
        }

        // Detectar si hay función main
        std::regex has_main(R"(^\s*int\s+main\s*\(.*\)\s*\{)"); // Función main
        if (std::regex_search(line, matches, has_main)) {
            code_block_.SetHasMain(true);
            return;
        }

    } catch (const std::regex_error& e) {
        std::cerr << "Regex error in line " << line_counter << ": " << e.what() << std::endl;
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
        if (comment.GetType() == "description" && comment.GetIsDescription()) {
            report_file << "DESCRIPTION:\n";
            report_file << comment.GetContent();  // Mostrar el contenido de la descripción
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
    }

    report_file << "\nSTATEMENTS:\n";
    for (const auto& loop : code_block_.GetLoops()) {
        report_file << loop << "\n";
    }

    // Imprimir si tiene main
    report_file << "\nMAIN:\n";
    report_file << (code_block_.HasMain() ? "True\n" : "False\n");

    // Imprimir comentarios de ambos tipos
    report_file << "\nCOMMENTS:\n";
    for (const auto& comment : code_block_.GetComments()) {
        if (comment.GetType() == "description" && comment.GetIsDescription()) {
            report_file << "[ Line " << comment.GetIniLine() << " - " << comment.GetEndLine() << "] DESCRIPTION\n";
            continue;  // Evitar imprimir el contenido real de la descripción
        }

        if (comment.GetType() == "single-line") {
            report_file << "[ Line " << comment.GetIniLine() << "] // " << comment.GetContent() << "\n";
        } else if (comment.GetType() == "multi-line") {
            report_file << "[ Line " << comment.GetIniLine() << " - " << comment.GetEndLine() << "] /* " << comment.GetContent() << " */\n";
        }
    }
}