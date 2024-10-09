/**
* Universidad de La Laguna
* Escuela Superior de Ingenieria y Tecnologia
* Informatica Basica
*
* @brief Ejercicios de programacion
* Version 1: Funcion factorial
*
* @see https :// github .com/IB -2023 -2024/ IB -class -code - examples /
*/ 

# include <iostream>
# include <cassert>

// Returns the factorial of the argument
int Factorial (int number) {
  switch ( number ) {
    case 0:
    case 1:
      return 1;
    default :
      double factorial = 1.0;
      for (int i = 1; i <= number ; ++ i ) {
        factorial *= i ;
      }
      return factorial ;
  }
}

// funcion main
int main () {
  std :: cout << " Introduzca el numero de factoriales a calcular : ";
  double limit;
  std :: cin >> limit ;
  for (int i = 1; i <= limit ; ++ i ) {
    std :: cout << i << "! = " << ( double ) Factorial ( i ) << std :: endl ;
  }
  return 0;
}