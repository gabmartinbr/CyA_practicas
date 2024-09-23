#include "simbolo.h"
#include "cadena.h"
#include "alfabeto.h"
#include "lenguaje.h"

#include <fstream>
#include <vector>
#include <sstream>

// declaraciones de las funciones
void usageHelp();

void leerFicheroEntrada(const std::string& inputFile, const std::string& outputFile, int opcode);



int main(int argc, char* argv[]) {

  if (argc > 1 && std::string(argv[1]) == "--help") {
    usageHelp();  // Llama a la función de uso
    return 0; // Sale del programa
  }  

  if (argc != 4) {
    std::cerr << "Uso: " << argv[0] << "inputFile outputFile  opcode" << std::endl;
    return 1;
  }
  
  std::string archivoEntrada = argv[1];
  std::string archivoSalida = argv[2];
  int operationCode = std::stoi(argv[3]);

  leerFicheroEntrada(archivoEntrada, archivoSalida, operationCode);
  return 0;
}


// definiciones de las funciones

void leerFicheroEntrada(const std::string& inputFile, const std::string& outputFile, int opcode) {
  std::ifstream inFile(inputFile);
  std::ofstream outFile(outputFile);

  if (!inFile.is_open() || !outFile.is_open()) {
    std::cerr << "Error al abrir alguno de los archivos" << std::endl;
    return;
  }

  std::string linea;
  while (std::getline(inFile, linea)) { // leer linea por linea y guardar los dos strings en una variable string
    std::istringstream iss(linea);
    std::string stringCadena, stringAlfabeto;

    iss >> stringCadena >> stringAlfabeto;  // leer de dos en dos la línea y guardando la cadena y el alfabeto
    std::vector<Simbolo> simbolosCadena;
    Alfabeto simbolosAlfabeto(stringAlfabeto);

    for (char c : stringCadena) {  // convertir la cadena a vector de simbolos para usar en el constructor de cadena mas adelante
      simbolosCadena.push_back(Simbolo(c));
    }

    Cadena cadena(simbolosCadena, simbolosAlfabeto);  // crear cadena desde lo leido en archivo y se genera su alfabeto correspondiente(constructor de cadena)
    
    switch (opcode) {
      case 1: // Alfabeto
        outFile << cadena.getAlfabeto() << std::endl;
        break;
      case 2: // Longitud
        outFile << cadena.getLongitud() << std::endl;
        break;
      case 3: // Inversa
        outFile << cadena.getInversa() << std::endl;
        break;
      case 4: // Prefijos
        outFile << Lenguaje(cadena.getPrefijos()) << std::endl; // usa constructor de Lenguaje
        break;
      case 5: // Sufijos
        outFile << Lenguaje(cadena.getSufijos()) << std::endl; // usa constructor de Lenguaje
        break;
      default:
        std::cerr << "Código de operación no válido." << std::endl;
        break;
    }
  }

  inFile.close();
  outFile.close();
}


void usageHelp() {
  std::cout << "Uso: p2_cadenas_lenguajes [opciones] [archivos]\n";
  std::cout << "Opciones:\n";
  std::cout << "  --help       Mostrar ayuda de uso\n";
  std::cout << "------------------------\n";
  std::cout << "Descripción:\n";
  std::cout << "Este programa acepta ficheros que contengan cadenas y alfabetos.\n";
  std::cout << "Formato de los ficheros de entrada:\n";
  std::cout << "  - Cada línea contiene una cadena y posteriormente una secuencia de simbolos, siendo el alfabeto de la cadena.\n";
  std::cout << "  - Los símbolos deben ser caracteres únicos.\n";
  std::cout << "\n";
  std::cout << "OPCODEs:\n";
  std::cout << "  - 1. ALFABETO\n";
  std::cout << "  - 2: LONGITUD\n";
  std::cout << "  - 3: CADENA INVERSA\n";
  std::cout << "  - 4: PREFIJOS\n";
  std::cout << "  - 5: SUFIJOS\n";
  std::cout << " \n";
  std::cout << "  - 0: EXIT\n";
}