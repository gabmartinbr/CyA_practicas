// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 2: Cadenas y lenguajes
// Autor: Gabriel Martín Broock
// Correo: alu0101539157@ull.edu.es
// Fecha: 22/09/2024
// Archivo simbolo.h: clase simbolo.
// Contiene la declaración de la clase simbolo 
// para poder usar objetos tipo símbolos para la creación de cadenas
// Referencias:
// Enlaces de interés /
// Historial de revisiones:
// 19/09/2024 - Creación (primera versión) del código

#ifndef SIMBOLO_H
#define SIMBOLO_H   

#include <iostream>

class Simbolo {
private:
  char simbolo_;

public:
  // constructor de simbolo
  Simbolo(char simbolo);

  // getter
  char getSimbolo() const;

  // sobrecarga del operador< para el uso de simbolos en set
  bool operator<(const Simbolo& otro) const;

  // sobrecarga del operador<< para imprimir simbolos
  friend std::ostream& operator<<(std::ostream& os, const Simbolo& simbolo);

};
#endif  // SIMBOLO_H