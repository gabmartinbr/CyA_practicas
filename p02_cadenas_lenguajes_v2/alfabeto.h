// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 2: Cadenas y lenguajes
// Autor: Gabriel Martín Broock
// Correo: alu0101539157@ull.edu.es
// Fecha: 22/09/2024
// Archivo alfabeto.h: clase alfabeto.
// Contiene la declaración de la clase alfabeto 
// para poder usar objetos tipo alfabeto(set de simbolos) y 
// realizar operaciones a las mismas
// Referencias:
// Enlaces de interés /
// Historial de revisiones:
// 19/09/2024 - Creación (primera versión) del código
#ifndef ALFABETO_H
#define ALFABETO_H
#include <set>
#include <string>
#include <stdexcept>  // Para std::invalid_argument
#include <iostream>
#include "simbolo.h"

class Alfabeto {
private:
  // conjunto set de simbolos
  std::set<Simbolo> simbolos_;

public:
  // constructor de alfabeto a partir de los simbolos
  Alfabeto();
  Alfabeto(const std::set<Simbolo>& simbolos);
  Alfabeto(const std::string& cadenaAlfabeto);

  // getter de conjunto de símbolos
  const std::set<Simbolo>& getSimbolos() const;

  // método para agregar un nuevo símbolo al set 
  void addSimbolo(const Simbolo& simbolo);

  // método para comprobar si ya está incluido un símbolo
  bool hasSimbolo(const Simbolo& simbolo) const;

  // sobrecarga de operador de salida para mostrar alfabeto = {a, b, c}
  friend std::ostream& operator<<(std::ostream& os, const Alfabeto& alfabeto);

};

#endif  // ALFABETO_H   