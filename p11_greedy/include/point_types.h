#pragma once

#include <iostream>
#include <utility>
#include <vector>
#include <set>

#define MAX_SZ 3  ///< Tamaño máximo, utilizado para redondeo o formato de salida.
#define MAX_PREC 0 ///< Precisión máxima para la representación numérica.

namespace CyA
{
    /**
     * @brief Representa un punto en un espacio bidimensional
     * 
     * primer elemento es la coordenada x y el segundo es la coordenada y.
     */
    typedef std::pair<double, double> point;

    /**
     * @brief Representa una línea ¡
     * 
     * definida como un par de point, que representan sus extremos.
     */
    typedef std::pair<point, point> line;

    /**
     * @brief Representa un vector de puntos.
     * 
     * colección ordenada de point
     */
    typedef std::vector<point> point_vector;

    /**
     * @brief Representa un arco
     * 
     * El arco se define como un par de point, indicando su inicio y fin.
     */
    typedef std::pair<point, point> arc;

    /**
     * @brief Representa un arco con peso.
     * 
     * un arco pesado incluye un valor de peso double junto con un arc
     * el peso puede representar distancia, costo
     */
    typedef std::pair<double, arc> weighted_arc;

    /**
     * @brief Representa un vector de arcos con peso.
     * 
     * colección de weighted_arc utilizada para representar un árbol/grafo
     */
    typedef std::vector<weighted_arc> arc_vector;

    /**
     * @brief Representa un conjunto único de puntos.
     * 
     * no permite duplicados y está ordenado según el criterio del tipo point, es decir, por coordenadas
     */
    typedef std::set<point> point_collection;

    /**
     * @brief Representa un árbol de arcos.
     * 
     * El árbol está compuesto por una colección de arc que no forman ciclos,
     */
    typedef std::vector<arc> tree;
}

/**
 * @brief Sobrecarga del operador de salida para un vector de puntos.
 * 
 * Este operador permite escribir el contenido de un CyA::point_vector en un flujo de salida.
 * 
 * @param os Flujo de salida donde se escribirá el vector de puntos.
 * @param ps Vector de puntos CyA::point_vector que será escrito.
 * @return std::ostream& Referencia al flujo de salida modificado.
 */
std::ostream& operator<<(std::ostream& os, const CyA::point_vector& ps);

/**
 * @brief Sobrecarga del operador de salida para un punto.
 * 
 * Este operador permite escribir un CyA::point en un flujo de salida.
 * 
 * @param os Flujo de salida donde se escribirá el punto.
 * @param ps Punto CyA::point que será escrito.
 * @return std::ostream& Referencia al flujo de salida modificado.
 */
std::ostream& operator<<(std::ostream& os, const CyA::point& ps);

/**
 * @brief Sobrecarga del operador de entrada para un vector de puntos.
 * 
 * Este operador permite leer el contenido de un CyA::point_vector desde un flujo de entrada.
 * 
 * @param is Flujo de entrada desde donde se leerá el vector de puntos.
 * @param ps Vector de puntos CyA::point_vector en el que se guradarán.
 * @return std::istream& Referencia al flujo de entrada modificado.
 */
std::istream& operator>>(std::istream& is, CyA::point_vector& ps);

/**
 * @brief Sobrecarga del operador de entrada para un punto.
 * 
 * Este operador permite leer un CyA::point desde un flujo de entrada.
 * 
 * @param is Flujo de entrada desde donde se leerá el punto.
 * @param ps Punto CyA::point que será llenado.
 * @return std::istream& Referencia al flujo de entrada modificado.
 */
std::istream& operator>>(std::istream& is, CyA::point& ps);