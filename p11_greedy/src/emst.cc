#include "point_types.h"
#include "emst.h"
#include "algorithm"

namespace EMST { 

    // constructor 
    point_set::point_set(const CyA::point_vector &points) 
    : CyA::point_vector(points), emst_() {}

    // destructor
    point_set::~point_set() {}

    // Método para calcular el EMST
    void point_set::EMST(void)
    {
        CyA::arc_vector av;
        compute_arc_vector(av);                             // calcular todas las aristas de los puntos

        forest st;                                          // árbol inicial, cada punto es un sub-árbol independiente

        for (const CyA::point &p : *this) 
        {
            sub_tree s;                                     // crear un sub_tree para cada punto
            s.add_point(p);

            st.push_back(s);                                // se agrega al bosque
        }

        for (const CyA::weighted_arc &a : av)               // recorrer las aristas por distancia creciente
        {
            int i, j;
            find_incident_subtrees(st, a.second, i, j);     // encontrar sub_tree que contengan los extremos i y j

            if (i != j)                                     // si i y j están en sub_tree distintos, se fusionan
            {
                merge_subtrees(st, a.second, i, j);
            }
        }

        emst_ = st[0].get_arcs();                           // st[0] es el árbol mínimo generador, guardado en emst_
    }
    

    // Método para escribir el árbol generador mínimo
    void point_set::write_tree(std::ostream &os) const {
        for (const auto &arc : emst_) {                     // para cada arco del árbol, se escribe sus extremos y distancia
            os << arc.second.first <<
            " - " << 
            arc.second.second << 
            " (dist: " << arc.first << ")" << 
            std::endl;
        }
    }

    // Método para escribir los puntos
    void point_set::write(std::ostream &os) const {
        for (const auto &point : *this) {                   // para cada punto, se imprime sus coordenadas
            os << point.first << 
            " " << 
            point.second << 
            std::endl;
        }
    }

    // Método para calcular todas las aristas posibles y ordenarlas
    void point_set::compute_arc_vector(CyA::arc_vector &av) const {
        av.clear();                                         // limpiar el vector por si se llama el método varias veces
        const int n = size();                               // obtener el número de puntos almacenados en point_set(hereda)

        for (int i = 0; i < n - 1; ++i) {                   // recorrer todos los puntos del set menos el último ya que no quedan puntos para emparejar
            const CyA::point &p_i = (*this)[i];             // punto i
            for (int j = i + 1; j < n; ++j) {
                const CyA::point &p_j = (*this)[j];         // punto j
                const double dist = euclidean_distance(std::make_pair(p_i, p_j));   // calcular distancia creando un par, arista con i,j 
                av.push_back(std::make_pair(dist, std::make_pair(p_i, p_j)));       // guardar la distancia y punto como par de i,j 
            }
        }
        std::sort(av.begin(), av.end());                    // ordenar en av según dist
    }

    // Método para buscar los subárboles incidentes a un arco
    void point_set::find_incident_subtrees(const forest &st, const CyA::arc &a, int &i, int &j) const {
        i = j = -1;                                         // indicador de que aún no se ha encontrado un sub_tree que contenga uno de los puntos del arco
        for (int k = 0; k < st.size(); ++k) {               // recorrer cada sub_tree en st(vector de sub_tree)
            if (st[k].contains(a.first)) {                  // comprobar que el primer punto del arco esta en el sub_tree de la pos k en st
                i = k;                                      // si está, st[k] contiene el primer punto del arco
            }
            if (st[k].contains(a.second)) {
                j = k;
            }
            if (i != -1 && j != -1) {                       // Ambos extremos encontrados en sub_tree diferentes
                break; 
            }
        }
    }

    // Método para calcular la distancia euclidiana entre dos puntos
    double point_set::euclidean_distance(const CyA::arc &a) const {
        const CyA::point &p1 = a.first;                     // primer punto del arco
        const CyA::point &p2 = a.second;                    // segundo punto del arco
        return std::sqrt(std::pow(p2.first - p1.first, 2) + std::pow(p2.second - p1.second, 2));    // fórmula de dist eucl
    }

    // Método para fusionar dos subárboles usando un arco
    void point_set::merge_subtrees(forest &st, const CyA::arc &a, int i, int j) const {
        st[i].merge(st[j], std::make_pair(euclidean_distance(a), a));           // usar sub_tree::merge para usar un arco para conectar dos sub_trees
        st.erase(st.begin() + j);                                               // Elimina el subárbol j después de la fusión
    }

    // Método para calcular el costo total del árbol generador mínimo
    double point_set::compute_cost() const {
        double total_cost = 0.0;                            // coste inicial
        for (const auto &arc : emst_) {                     // recorrer cada arco en el emst
            total_cost += euclidean_distance(arc);          // coste total es la suma de cada eucl dist de los arcos
        }
        return total_cost;
    }

} // namespace EMST

