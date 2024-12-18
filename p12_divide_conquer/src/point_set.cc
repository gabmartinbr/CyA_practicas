#include "point_set.h"
#include <cmath>
#include <algorithm>
#include <limits>

namespace CyA {

    point_set::point_set(const point_vector &points) : point_vector(points) {}

    point_set::~point_set() {}

    void point_set::quickHull(void) {
        hull_.clear();

        CyA::point min_x_point; 
        CyA::point max_x_point;

        x_bounds(min_x_point, max_x_point);

        quickHull(CyA::line(min_x_point, max_x_point), side::LEFT);
        quickHull(CyA::line(min_x_point, max_x_point), side::RIGHT);

        std::sort(hull_.begin(), hull_.end());
        hull_.erase(std::unique(hull_.begin(), hull_.end()), hull_.end());
    }

    void point_set::write_hull(std::ostream &os) const {
        for (const point &p : hull_) {
            os << "(" << p.first << ", " << p.second << ")" << std::endl;
        }
    }

    void point_set::write_dot(std::ostream &os) const {
        os << "graph G {" << std::endl;  // Comienza la definición del grafo en formato DOT

        // Definir los puntos de la envolvente convexa
        for (size_t i = 0; i < hull_.size(); ++i) {
            os << "    " << i << " [label=\"" << hull_[i].first << ", " << hull_[i].second << "!\"];" << std::endl;
        }

        // Añadir las aristas entre los puntos consecutivos de la envolvente
        for (size_t i = 0; i < hull_.size(); ++i) {
            os << "    " << i << " -- " << (i + 1) % hull_.size() << ";" << std::endl;  // Crea una arista entre los puntos
        }

        os << "}" << std::endl;  // Cierra la definición del grafo en formato DOT
    }

    void point_set::quickHull(const CyA::line &l, int side) {
        CyA::point farthest;
        if (farthest_point(l, side, farthest)) {
        quickHull(CyA::line(l.first, farthest), -find_side(CyA::line(l.first, farthest), l.second));
        quickHull(CyA::line(farthest, l.second), -find_side(CyA::line(farthest, l.second), l.first));
        } else {
            hull_.push_back(l.first);
            hull_.push_back(l.second);
        }
    }

    double point_set::distance(const line &l, const point &p) const {
        return std::abs((l.second.second - l.first.second) * p.first - 
                        (l.second.first - l.first.first) * p.second + 
                        l.second.first * l.first.second - 
                        l.second.second * l.first.first) /
               std::sqrt(std::pow(l.second.second - l.first.second, 2) +
                         std::pow(l.second.first - l.first.first, 2));
    }

    int point_set::find_side(const line &l, const point &p) const {
        double val = point_2_line(l, p);  // Calcula la posición relativa de p con respecto a la línea l.
        if (val > 0) return LEFT;          // Si el valor es positivo, el punto está a la izquierda de la línea
        if (val == 0) return CENTER;       // Si el valor es 0, el punto está sobre la línea
        return RIGHT;                      // Si el valor es negativo, el punto está a la derecha de la línea
    }

    void point_set::x_bounds(point &min_x, point &max_x) const {
    min_x = max_x = at(0);  // Inicializamos los puntos más a la izquierda y derecha como el primer punto.
    for (const point &p : *this) {
        if (p.first < min_x.first) {
            min_x = p;  // Actualizamos el punto más a la izquierda
        }
        if (p.first > max_x.first) {
            max_x = p;  // Actualizamos el punto más a la derecha
        }
    }
}

    double point_set::point_2_line(const line &l, const point &p) const {
        // Calcula el valor relativo de un punto respecto a una línea
        return (l.second.second - l.first.second) * (p.first - l.first.first) -
            (l.second.first - l.first.first) * (p.second - l.first.second);
    }

    bool point_set::farthest_point(const CyA::line &l, int side, CyA::point &farthest) const {
        farthest = CyA::point_vector::at(0);  // Inicializamos el punto más alejado con el primer punto del conjunto
        double max_dist = 0;
        bool found = false;

        // Recorremos todos los puntos para encontrar el más alejado
        for (const CyA::point &p : *this) {
            // Solo consideramos el punto si está en el lado adecuado de la línea
            if (find_side(l, p) == side) {
                // Calculamos la distancia entre el punto p y la línea l
                const double dist = distance(l, p);
                std::cout << "Evaluando punto: (" << p.first << ", " << p.second << ") con distancia: " << dist << std::endl;

                // Si la distancia es mayor que la distancia máxima encontrada, actualizamos el punto más alejado
                if (dist > max_dist) {
                    farthest = p;
                    max_dist = dist;
                    found = true;
                }
            }
        }

        return found;
    }
}