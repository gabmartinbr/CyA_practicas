#include "simbolo.h"
#include "cadena.h"
#include "alfabeto.h"
#include "lenguaje.h"

#include <fstream>
#include <vector>
#include <sstream>


// opción de --help para el programa
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

// funcion de lectura de archivo y creacion de cadena de simbolos y alfabetos de simbolos
void leerFicheroEntrada(const std::string& fileName, std::vector<Cadena>& cadenas) {
    std::ifstream archivo(fileName);
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo de entrada" << std::endl;
        return;
    }

    std::string line;
    while (std::getline(archivo, line)) {
        std::istringstream stream(line);
        std::string cadenaStream;

        // Leer solo la cadena
        if (stream >> cadenaStream) {
            std::vector<Simbolo> simbolos; // Para los símbolos de la cadena
            Alfabeto alfabeto; // Nuevo alfabeto para cada cadena

            for (char c : cadenaStream) {
                Simbolo simbolo(c);
                simbolos.push_back(simbolo);
                alfabeto.addSimbolo(simbolo); // Agregar símbolo al alfabeto
            }

            Cadena cadena(simbolos); // Crear objeto cadena con su respectivo alfabeto
            cadenas.push_back(cadena); // Añadir cadena al vector
        }
    }
    archivo.close();
}

// Función para escribir el alfabeto de cada cadena en un archivo de salida
void escribirAlfabetos(const std::vector<Alfabeto>& alfabetos, const std::string& outFile) {
  std::ofstream archivo(outFile);
  if (!archivo.is_open()) {
    std::cerr << "Error al abrir o crear archivo" << std::endl;
    return;
  }

  // Iterar sobre cada alfabeto en el vector
  for (const auto& alfabeto : alfabetos) {
    archivo << alfabeto << std::endl;  // Escribir alfabeto en una nueva línea
  }
  std::cout << alfabetos.size();
  archivo.close();
}


void escribirLongitudes(const std::vector<Cadena>& cadenas, const std::string& outFile) {
  std::ofstream archivo(outFile);
  if (!archivo.is_open()) {
    std::cerr << "Error al abrir o crear archivo" << std::endl;
    return;
  }

  // Iterar sobre cada cadena en el vector
  for (const auto& cadena : cadenas) {
    size_t longitud = cadena.getLongitud();
    archivo << longitud << std::endl;  // Escribir longitud en una nueva línea
  }

  archivo.close();
}

void escribirInversas(const std::vector<Cadena>& cadenas, const std::string& outFile) {
  std::ofstream archivo(outFile);
  if (!archivo.is_open()) {
    std::cerr << "Error al abrir o crear archivo" << std::endl;
    return;
  }

  for (const auto& cadena : cadenas) {
    // Obtener la inversa de la cadena
    auto inversa = cadena.inversa();
    // Escribir la cadena inversa en el archivo
    for (const auto& simbolo : inversa) {
      archivo << simbolo.getSimbolo();  // escribir simbolos de la inversa
    }
    archivo << std::endl;  // Nueva línea para la siguiente cadena
  }
  archivo.close();
}




int main() {
    // Crear un alfabeto
    Alfabeto alfabeto;


    // Crear una cadena utilizando el alfabeto
    std::vector<Simbolo> simbolos = {Simbolo('z'), Simbolo('a'), Simbolo('r'), Simbolo('b')};
    Cadena cadena(simbolos);

    // Obtener el alfabeto de la cadena y mostrarlo
    const Alfabeto& alfabetoDeCadena = cadena.getAlfabeto();
    std::cout << "Alfabeto de la cadena: " << alfabetoDeCadena << std::endl;

    return 0;
}