#pragma once

#include <iostream>
#include <cmath>

#include "point_types.h"

namespace EMST {
  /**
   * @brief representa un sub_tree dentro de un emst
   * 
   * un sub_tree encapsula una colección de arcos CyA::tree, 
   * puntos CyA::point_collection y el coste acumulado del sub_tree
   * 
   */
  class sub_tree {
    private:
      CyA::tree arcs_;                ///< colección de arcos que forman el sub_tree
      CyA::point_collection points_;  ///< colección de puntos contenidos en el sub_tree
      double cost_;                   ///< coste acumulado del sub_tree

    public:

      /**
       * @brief constructor, inicializa un sub_tree vacío
       */
      sub_tree(void);

      /**
       * @brief destructor, libera los recursos del sub_tree
       * 
       */
      ~sub_tree(void);

      /**
       * @brief agrega un arco 
       * 
       * @param a arco a añadir
       */
      void add_arc(const CyA::arc &a);

      /**
       * @brief añade un punto
       * 
       * @param p punto a añadir
       */
      void add_point(const CyA::point &p);

      /**
       * @brief verifica si un punto está contenido en el sub_tree
       * 
       * @param p punto a verificar
       * @return true 
       * @return false 
       */
      bool contains(const CyA::point &p) const;

      /**
       * @brief fusiona el sub_tree actual con otro
       * combinando los arcos, puntos y costes, usando
       * un arco ponderado como enlace entre ambos
       * 
       * @param st sub_tree a fusionar con el actual
       * @param a arco ponderado de enlace
       */
      void merge(const sub_tree &st, const CyA::weighted_arc &a);
      
      /**
       * @brief getter de los arcos del sub_tree
       * 
       * @return const CyA::tree& 
       */
      inline const CyA::tree& get_arcs(void) const { return arcs_; }

      /** getter del coste total del sub_tree
       * 
       *  @return double cost_
       */
      inline double get_cost(void) const { return cost_; }

  };

  /**
   * @brief representa un vector de sub_tree de forma ordenada
   * 
   */
  typedef std::vector<sub_tree> sub_tree_vector;
  
}
