#include <iostream>
#include <fstream>
#include "emst.h"
#include "point_types.h"

int main(int argc, char* argv[]) {
    // verificar al menos un parámetro, archivo de entrada
    if (argc < 2) {
        std::cerr << "Error: debes proporcionar un archivo de entrada. " << std::endl;
        return 1;
    }

    // Leer los puntos desde el archivo proporcionado
    CyA::point_vector points;
    std::ifstream input(argv[1]);
    if (input.is_open()) {
        input >> points;
        input.close();
    } else {
        std::cerr << "Error: no se pudo abrir el archivo de entrada: " << argv[1] << std::endl;
        return 1;
    }

    // Crear el objeto point_set con los puntos leídos
    EMST::point_set ps(points);

    // Calcular el Árbol Generador Mínimo (EMST)
    ps.EMST();

    // Verificar opcion -d
    bool create_dot = false;
    if (argc > 2 && std::string(argv[2]) == "-d") {
        create_dot = true;
    }

    // Si la opción -d está presente, guardar el resultado en un archivo .dot
    if (create_dot) {
        std::ofstream output("data/output.dot");
        if (output.is_open()) {
            ps.write_dot_format(output);
            output.close();
            std::cout << "El árbol fue guardado en formato .dot en 'output.dot'." << std::endl;
        } else {
            std::cerr << "Error al abrir el archivo para guardar el archivo .dot." << std::endl;
            return 1;
        }
    } else {
        // Si no se pasa la opción -d, solo mostrar el árbol en la consola
        std::cout << "Árbol Generador Mínimo (EMST): " << std::endl;
        ps.write_tree(std::cout);
    }

    return 0;
}