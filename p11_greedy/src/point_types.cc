#include "point_types.h"
#include <iomanip>

// Sobrecargar el operador >> para CyA::point
std::istream& operator>>(std::istream& is, CyA::point& p) {
    // Leer las coordenadas x y y
    is >> p.first >> p.second;
    return is;
}

// Sobrecargar el operador >> para CyA::point_vector (std::vector<CyA::point>)
std::istream& operator>>(std::istream& is, CyA::point_vector& ps) {
    int n;
    is >> n;  // Leer el número de puntos

    ps.clear();  // Limpiar el vector antes de agregar nuevos puntos

    for (int i = 0; i < n; ++i) {
        CyA::point p;
        is >> p;  // Leer un punto
        ps.push_back(p);  // Añadir el punto al vector
    }

    return is;
}

// Sobrecargar el operador << para CyA::point_vector (std::vector<CyA::point>)
std::ostream& operator<<(std::ostream& os, const CyA::point_vector& ps) {
    os << ps.size() << std::endl;
    for (const CyA::point& p : ps) {
        os << p << std::endl;  // Usar el operador << para cada punto
    }
    return os;
}

// Sobrecargar el operador << para CyA::point
std::ostream& operator<<(std::ostream& os, const CyA::point& p) {
    os << std::setw(MAX_SZ) << std::fixed << std::setprecision(MAX_PREC)
       << p.first << "\t" << std::setw(MAX_SZ) << std::fixed
       << std::setprecision(MAX_PREC) << p.second;
    return os;
}