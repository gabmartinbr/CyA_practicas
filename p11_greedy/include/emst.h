#pragma once

#include <vector>
#include "sub_tree.h"  // Incluye el archivo que define sub_tree.

namespace EMST {
    
    /**
     * @brief representar un bosque como un vector de sub_tree
     */
    typedef std::vector<sub_tree> forest;

    /**
     * @brief clase para manejar conjunto de puntos y calcular el emst
     * 
     * hereda de CyA::point_vector
     */
    class point_set : public CyA::point_vector {
    private:
        CyA::tree emst_;    ///< árbol generador mínimo resultante

    public:
        /**
         * @brief constructor
         * 
         * @param points vector de puntos iniciales
         */
        point_set(const CyA::point_vector &points);

        /**
         * @brief destructor
         */
        ~point_set(void);

        /**
         * @brief calcula el árbol generador mínimo euclidiano del conjunto de puntos
         */
        void EMST(void);

        /**
         * @brief escribe el emst en un flujo de salida en formato: pos_p1 -> pos_p2 ... coste total
         * 
         * @param os flujo de salida donde se escribe
         */
        void write_tree(std::ostream &os) const;

        /**
         * @brief escribe los puntos de forma legible, imprimiendo sus coordenadas
         * 
         * @param os flujo de salida donde se escribe
         */
        void write(std::ostream &os) const;

        /**
         * @brief escribe el emst en formato .dot para su visualización graphview(neato) 
         * 
         * @param os flujo de salida donde se escribe
         */
        void write_dot_format(std::ostream &os) const;

        /**
         * @brief getter de tree(emst)
         * 
         * @return const CyA::tree& 
         */
        inline const CyA::tree& get_tree(void) const { return emst_; }

        /**
         * @brief getter de puntos del conjunto
         * 
         * @return const CyA::point_vector& 
         */
        inline const CyA::point_vector& get_points(void) const { return *this; }

        /**
         * @brief getter del resultado de calcular el coste total del emst
         * 
         * @return const double 
         */
        inline const double get_cost(void) const { return compute_cost(); }

    private:

        /**
         * @brief calcula un vector de arcos necesarios para construir el emst(todos los arcos posibles)
         * 
         * @param av vector de arcos que se actualiza con los arcos calculados
         */
        void compute_arc_vector(CyA::arc_vector &av) const; 

        /**
         * @brief encuentra sub_tree incidentes a un arco dado
         * 
         * @param st forest de sub_tree
         * @param a arco a analizar
         * @param i índice del primer sub_tree
         * @param j índice del segundo sub_tree
         */
        void find_incident_subtrees(const forest& st, const CyA::arc &a, int& i, int& j) const;

        /**
         * @brief fusiona dos sub_tree en el bosque
         * 
         * @param st forest de sub_tree
         * @param a arco que conecta los sub_tree
         * @param i índice del primer sub_tree
         * @param j índice del segundo sub_tree
         */
        void merge_subtrees(forest& st, const CyA::arc &a, int i, int j) const;

        /**
         * @brief calcula el coste total del emst
         * 
         * @return double 
         */
        double compute_cost(void) const;

        /**
         * @brief calcula la dist euclidiana de un arco
         * 
         * @param a arcos de los cuales se usarán sus extremos para el cálculo
         * @return double 
         */
        double euclidean_distance(const CyA::arc& a) const;
    };

}  // namespace EMST

