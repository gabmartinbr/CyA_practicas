#pragma once

#include <iostream>
#include <utility>
#include <vector>
#include <set>

#define MAX_SZ 3
#define MAX_PREC 0

namespace CyA
{
  typedef std::pair<double, double> point;        // punto 2D

  typedef std::pair<point, point> line;           // linea
  typedef std::vector<point> point_vector;        //

  typedef std::pair<point, point> arc;            // arco 
  typedef std::pair<double, arc> weighted_arc;    // arco pesado
  typedef std::vector<weighted_arc> arc_vector;   // vector de arcos

  typedef std::set<point> point_collection;       // conjunto de puntos
  
  typedef std::vector<arc> tree;                  // arbol de arcos 
}

std::ostream& operator<<(std::ostream& os, const CyA::point_vector& ps);
std::ostream& operator<<(std::ostream& os, const CyA::point& ps);

std::istream& operator>>(std::istream& is, CyA::point_vector& ps);
std::istream& operator>>(std::istream& is, CyA::point& ps);

