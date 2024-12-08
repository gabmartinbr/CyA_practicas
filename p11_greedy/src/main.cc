#include <iostream>
#include <fstream>
#include "emst.h"
#include "point_types.h"

int main() {
    // Leer los puntos desde un archivo o crearlos manualmente
    CyA::point_vector points;

    // Si deseas leer desde un archivo:
    std::ifstream input("data/input1.txt");
    if (input.is_open()) {
        input >> points;
        input.close();
    } else {
        // Si no se pudo abrir el archivo, puedes agregar puntos manualmente
        points.push_back(CyA::point(0.0, 0.0));
        points.push_back(CyA::point(1.0, 0.0));
        points.push_back(CyA::point(1.0, 1.0));
        points.push_back(CyA::point(0.0, 1.0));
    }

    // Crear el objeto point_set con los puntos leídos
    EMST::point_set ps(points);

    // Calcular el Árbol Generador Mínimo (EMST)
    ps.EMST();

    // Imprimir el árbol generador mínimo
    std::cout << "Árbol Generador Mínimo:" << std::endl;
    ps.write_tree(std::cout);

    // Imprimir el costo total del árbol generador mínimo
    std::cout << "Costo total del EMST: " << ps.get_cost() << std::endl;

    // Opcionalmente, guardar el árbol en un archivo
    std::ofstream output("emst_result.txt");
    if (output.is_open()) {
        ps.write_tree(output);
        output.close();
    } else {
        std::cerr << "Error al abrir el archivo para guardar el resultado." << std::endl;
    }

    return 0;
}