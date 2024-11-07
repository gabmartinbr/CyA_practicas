#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>
#include "grammar.h"

int main(int argc, char* argv[]) {
    // Verificamos si los argumentos son correctos
    if (argc != 3) {
        std::cerr << "Modo de empleo: ./Grammar2CNF input.gra output.gra" << std::endl;
        std::cerr << "Pruebe 'Grammar2CNF --help' para más información." << std::endl;
        return 1;
    }

    // Obtener nombres de los archivos de entrada y salida
    const std::string inputFileName = argv[1];
    const std::string outputFileName = argv[2];

    // Abrimos el archivo de entrada
    std::ifstream inputFile(inputFileName);
    if (!inputFile.is_open()) {
        std::cerr << "No se pudo abrir el archivo de entrada: " << inputFileName << std::endl;
        return 1;
    }

    Grammar grammar;  // Crear un objeto Grammar no constante

    // Leer la gramática desde el archivo
    grammar.readGrammar(inputFile);
    inputFile.close();  // Cerramos el archivo de entrada

    // Realizamos la conversión a Forma Normal de Chomsky (si es necesario)
    grammar.converterCNF();

    // Abrimos el archivo de salida
    std::ofstream outputFile(outputFileName);
    if (outputFile.is_open()) {
        // Escribimos la gramática convertida en el archivo de salida
        grammar.writeGrammar(outputFileName);
        outputFile.close();  // Cerramos el archivo de salida
    } else {
        std::cerr << "No se pudo abrir el archivo de salida: " << outputFileName << std::endl;
        return 1;
    }

    return 0;
}