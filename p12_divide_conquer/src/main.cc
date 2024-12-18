#include "point_set.h"
#include <fstream>

int main(int argc, char *argv[]) {
    
    if (argc < 2) {
        std::cerr << "Error: debes proporcionar archivo de entrada" << std::endl;
        return 1;
    }

    // Leer los puntos desde el archivo proporcionado
    CyA::point_vector points;
    std::ifstream input(argv[1]);
    if (input.is_open()) {
        size_t n;
        input >> n;
        points.resize(n);
        for (size_t i = 0; i < n; ++i) {
            input >> points[i].first >> points[i].second;
        }
        input.close();
    } else {
        std::cerr << "Error: no se pudo abrir el archivo de entrada: " << argv[1] << std::endl;
        return 1;
    }

    // Crear el objeto point_set con los puntos leídos
    CyA::point_set ps(points);

    // Calcular la envolvente convexa
    ps.quickHull();

    // Verificar opción -d
    bool create_dot = (argc > 2 && std::string(argv[2]) == "-d");

    if (create_dot) {
            std::ofstream output("hull_output.dot");
            if (output.is_open()) {
                ps.write_dot(output);
                std::cout << "Se ha generado el archivo .dot para Graphviz: 'hull_output.dot'" << std::endl;
            } else {
                std::cerr << "Error al abrir el archivo para generar el archivo .dot." << std::endl;
                return 1;
            }
        } else {
            // Mostrar la envolvente convexa en la consola
            std::cout << "La envolvente convexa es:" << std::endl;
            ps.write_hull(std::cout);
        }

    return 0;
}