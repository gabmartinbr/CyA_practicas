// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 2: Cadenas y lenguajes
// Autor: Gabriel Martín Broock
// Correo: alu0101539157@ull.edu.es
// Fecha: 22/09/2024
// Archivo cadena.h: clase cadena.
// Contiene la declaración de la clase cadena 
// para poder usar objetos tipo cadena(vector de simbolos) y 
// realizar operaciones a las mismas
// Referencias:
// Enlaces de interés /
// Historial de revisiones:
// 19/09/2024 - Creación (primera versión) del código

#ifndef CADENA_H
#define CADENA_Hs

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

  // constructor para formar cadena a partir de un vector de simbolos
  Cadena();
  Cadena(const std::vector<Simbolo>& simbolos);
  
  // getter para obtener la cadena 
  const std::vector<Simbolo>& getCadena() const;
  // getter para obtener el alfabeto de dicha cadena
  const Alfabeto& getAlfabeto() const;

  // método para añadir simbolos a una cadena
  void addSimbolo(const Simbolo& simbolo);

  // comprobar si la cadena es válida
  bool isValid() const;

  // métodos para obtener sufijos y prefijos como set ordenado
  std::set<Cadena> getPrefijos() const;
  std::set<Cadena> getSufijos() const;

  // método que devuelve la cadena inversa 
  Cadena getInversa() const;

  // método que devuelve la longitud, numero de simbolos, de una cadena
  size_t getLongitud() const;

  // sobrecarga del operador< para el uso de cadenas ordenadas con set
  bool operator<(const Cadena& otra) const;

  // sobrecarga de operador<< para mostrar la cadena de forma abc...
  friend std::ostream& operator<<(std::ostream& os, const Cadena& cadena);
};

#endif  // CADENA_H