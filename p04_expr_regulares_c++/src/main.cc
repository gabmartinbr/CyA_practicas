#include<iostream>


/**
 * @brief funcion principal del programa analiazdor de código
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char* argv[]) {

  // error de argumentos incorrectos
  if (argc == 1) {
    std::cerr << "Usage: ./code_analysis <input_file_path> <output_file_path>" << std::endl;
    return 1;
  }
  
  // asignación de ficheros de entrada y salida desde los argumentos
  std::string input_file = argv[1];
  std::string output_file = argv[2];

  // crear objeto tipo CodeAnalysis
  CodeAnalysis analysis(input_file, output_file);
  // analizar archivo y crear reporte
  analysis.AnalizeFile();
  analysis.ExportReport();

  std::cout << "Analisis terminado, compruebe el fichero " << output_file << " para ver resultados" << std::endl;
  
  return 0;
}

