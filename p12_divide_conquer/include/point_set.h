#pragma once
#include <vector>
#include <utility>
#include <iostream>

namespace CyA {
        /**
         * @brief Representa un punto en un plano bidimensional.
         * 
         * Se define como un par de coordenadas (x, y) en formato double.
         */
        typedef std::pair<double, double> point;

        /**
         * @brief Representa una línea en un plano bidimensional.
         * 
         * Una línea está definida por dos puntos (inicio y fin).
         */
        typedef std::pair<point, point> line;

        /**
         * @brief Representa un conjunto de puntos en un plano bidimensional.
         * 
         * Se implementa como un vector de puntos.
         */
        typedef std::vector<point> point_vector;
        
        /**
         * @brief Define los posibles lados en relación a una línea.
         * 
         * LEFT   : El punto está a la izquierda de la línea.
         * CENTER : El punto está sobre la línea.
         * RIGHT  : El punto está a la derecha de la línea.
         */
        enum side {
                LEFT = -1,
                CENTER,
                RIGHT
        };
        
        /**
         * @brief Clase para manejar un conjunto de puntos y calcular la envolvente convexa.
         * 
         * La clase hereda de point_vector, lo que permite tratarla como un vector de puntos,
         * pero agrega funcionalidad específica para calcular la envolvente convexa usando el
         * algoritmo QuickHull.
         */
        class point_set : public point_vector {
        private:
                point_vector hull_; ///< Contenedor para almacenar los puntos de la envolvente convexa.

        public:
                /**
                 * @brief Constructor de la clase point_set.
                 * 
                 * Inicializa un conjunto de puntos a partir de un vector de puntos dado.
                 * 
                 * @param points Vector de puntos para inicializar el conjunto.
                 */
                point_set(const point_vector &points);

                /**
                 * @brief Destructor de la clase point_set.
                 */
                ~point_set(void);

                /**
                 * @brief Calcula la envolvente convexa utilizando el algoritmo QuickHull.
                 * 
                 * Este método divide el conjunto de puntos en dos mitades usando los puntos
                 * más a la izquierda y más a la derecha, y luego realiza llamadas recursivas
                 * para encontrar los puntos de la envolvente convexa en ambos lados.
                 */
                void quickHull(void);

                /**
                 * @brief Escribe los puntos de la envolvente convexa en un flujo de salida.
                 * 
                 * @param os Flujo de salida donde se escribirán los puntos.
                 */
                void write_hull(std::ostream &os) const;

                /**
                 * @brief Escribe todos los puntos del conjunto en un flujo de salida.
                 * 
                 * @param os Flujo de salida donde se escribirán los puntos.
                 */
                void write(std::ostream &os) const;

                /**
                 * @brief Genera un archivo en formato DOT que representa el grafo de la envolvente convexa.
                 * 
                 * @param os Flujo de salida donde se escribirá el contenido en formato DOT.
                 */
                void write_dot(std::ostream &os) const;

                /**
                 * @brief Obtiene los puntos de la envolvente convexa.
                 * 
                 * @return Referencia constante al vector de puntos que forman la envolvente convexa.
                 */
                inline const point_vector& get_hull(void) const { return hull_; }

                /**
                 * @brief Obtiene todos los puntos del conjunto.
                 * 
                 * @return Referencia constante al vector de puntos.
                 */
                inline const point_vector& get_points(void) const { return *this; }
 
        private:     
                /**
                 * @brief Calcula recursivamente los puntos de la envolvente convexa en un lado de una línea.
                 * 
                 * @param l Línea base para dividir el conjunto de puntos.
                 * @param side Lado de la línea en el que buscar los puntos de la envolvente convexa.
                 */
                void quickHull(const line &l, int side);

                /**
                 * @brief Calcula la distancia perpendicular de un punto a una línea.
                 * 
                 * @param l Línea a la que se calcula la distancia.
                 * @param p Punto cuya distancia se desea calcular.
                 * @return Distancia perpendicular del punto a la línea.
                 */
                double distance(const line &l, const point &p) const;

                /**
                 * @brief Determina en qué lado de una línea se encuentra un punto.
                 * 
                 * @param l Línea base para la evaluación.
                 * @param p Punto a evaluar.
                 * @return LEFT (-1) si el punto está a la izquierda, CENTER (0) si está sobre la línea, 
                 *         RIGHT (1) si está a la derecha.
                 */
                int find_side(const line &l, const point &p) const;
                
                /**
                 * @brief Encuentra los puntos más a la izquierda y más a la derecha del conjunto.
                 * 
                 * @param min_x Referencia donde se almacenará el punto más a la izquierda.
                 * @param max_x Referencia donde se almacenará el punto más a la derecha.
                 */
                void x_bounds(point &min_x, point &max_x) const;

                /**
                 * @brief Calcula la posición relativa de un punto respecto a una línea.
                 * 
                 * @param l Línea base para la evaluación.
                 * @param p Punto a evaluar.
                 * @return Valor positivo si el punto está a la izquierda de la línea, negativo si está a la derecha, 
                 *         y 0 si está sobre la línea.
                 */
                double point_2_line(const line &l, const point &p) const;

                /**
                 * @brief Encuentra el punto más alejado de una línea en un lado especificado.
                 * 
                 * @param l Línea base para la evaluación.
                 * @param side Lado de la línea en el que buscar el punto más alejado.
                 * @param farthest Referencia donde se almacenará el punto más alejado encontrado.
                 * @return true si se encontró un punto, false si no hay puntos en el lado especificado.
                 */
                bool farthest_point(const line &l, int side, point &farthest) const;
        };
}