// cadena.h
#ifndef CADENA_H
#define CADENA_H

#include <string>
#include <set>
#include <vector>
#include "alfabeto.h"
#include "simbolo.h"

// to-do: separar en .h y .cc

class Cadena {
private:  
  std::vector<Simbolo> cadena_;  // cadena como vector de simbolos
  Alfabeto alfabeto_;  // alfabeto correspondiente a la cadena
  
public:
  static const Simbolo CAD_VACIA; // definición de cadena vacía

  // constructor para formar cadena 
  Cadena(const std::vector<Simbolo>& simbolos);
  
  // getters para obtener la cadena y su respectivo alfabeto
  const std::vector<Simbolo>& getCadena() const;
  const Alfabeto& getAlfabeto() const;

  // setter para añadir simbolos
  void addSimbolo(const Simbolo& simbolo);

  // comprobar si la cadena es válida
  bool isValid() const;

  // métodos para obtener sufijos y prefijos
  std::set<std::vector<Simbolo>> getPrefijos() const;
  std::set<std::vector<Simbolo>> getSufijos() const;

  // método de inversa de una cadena
  std::vector<Simbolo> inversa() const;

  // longitud, numero de simbolos de una cadena
  size_t getLongitud() const;

  // sobrecarga del operador< para el uso de simbolos en set
  bool operator<(const Cadena& otra) const;

  // sobrecarga de operador<< para mostrar cadena = abc
  friend std::ostream& operator<<(std::ostream& os, const Cadena& cadena);
};

#endif  // CADENA_H