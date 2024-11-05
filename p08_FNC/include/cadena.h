#ifndef CADENA_H
#define CADENA_H

#include <string>
#include <set>
#include <vector>
#include "alfabeto.h"
#include "simbolo.h"

// Clase que representa una cadena de símbolos pertenecientes a un alfabeto.
class Cadena {
private:  
  std::vector<Simbolo> cadena_;  ///< Vector de símbolos que conforman la cadena.
  Alfabeto alfabeto_;  ///< Alfabeto correspondiente a la cadena.

public:
  static const Simbolo CAD_VACIA; ///< Definición de cadena vacía.

  /**
   * @brief Constructor por defecto de la clase Cadena.
   */
  Cadena();

  /**
   * @brief Constructor de la clase Cadena a partir de un vector de símbolos y un alfabeto.
   * 
   * @param simbolos Vector de símbolos que forman la cadena.
   * @param alfabeto Alfabeto al que pertenecen los símbolos.
   */
  Cadena(const std::vector<Simbolo>& simbolos, const Alfabeto& alfabeto);
  
  /**
   * @brief Getter para obtener la cadena.
   * 
   * @return const std::vector<Simbolo>& Referencia constante al vector de símbolos de la cadena.
   */
  const std::vector<Simbolo>& getCadena() const;

  /**
   * @brief Getter para obtener el alfabeto de la cadena.
   * 
   * @return const Alfabeto& Referencia constante al alfabeto de la cadena.
   */
  const Alfabeto& getAlfabeto() const;

  /**
   * @brief Método para añadir un símbolo a la cadena.
   * 
   * @param simbolo El símbolo a añadir a la cadena.
   */
  void addSimbolo(const Simbolo& simbolo);

  /**
   * @brief Método para comprobar si la cadena es válida.
   * 
   * @return true Si la cadena es válida.
   * @return false Si la cadena no es válida.
   */
  bool isValid() const;

  /**
   * @brief Método para obtener los prefijos de la cadena.
   * 
   * @return std::set<Cadena> Conjunto de prefijos de la cadena.
   */
  std::set<Cadena> getPrefijos() const;

  /**
   * @brief Método para obtener los sufijos de la cadena.
   * 
   * @return std::set<Cadena> Conjunto de sufijos de la cadena.
   */
  std::set<Cadena> getSufijos() const;

  /**
   * @brief Método que devuelve la cadena inversa.
   * 
   * @return Cadena Cadena invertida.
   */
  Cadena getInversa() const;

  /**
   * @brief Método que devuelve la longitud de la cadena.
   * 
   * @return size_t Número de símbolos en la cadena.
   */
  size_t getLongitud() const;

  /**
   * @brief Sobrecarga del operador < para el uso de cadenas ordenadas en un conjunto.
   * 
   * @param otra Otra cadena con la que se compara.
   * @return true Si esta cadena es menor que la otra.
   * @return false Si esta cadena no es menor que la otra.
   */
  bool operator<(const Cadena& otra) const;

  /**
   * @brief Sobrecarga del operador == para comparar cadenas
   * 
   * @param otra Otra cadena con la que se compara.
   * @return true Si esta cadena es igual que la otra.
   * @return false Si esta cadena no es igual que la otra.
   */
  bool operator==(const Cadena& otra) const;

  /**
   * @brief Sobrecarga del operador · para concatenar cadenas
   * 
   * @param os Flujo de salida.
   * @param otra cadena a concatenar
   * @return std::ostream& Referencia al flujo de salida.
   */
  Cadena operator+(const Cadena& otra) const;

  /**
   * @brief Sobrecarga del operador << para mostrar la cadena de forma legible.
   * 
   * @param os Flujo de salida.
   * @param cadena Objeto Cadena a mostrar.
   * @return std::ostream& Referencia al flujo de salida.
   */
  friend std::ostream& operator<<(std::ostream& os, const Cadena& cadena);



  // metodo de si una cadena es palindroma y poner true o false en archivo
  bool isPalindroma();
  // metodo de potencia de una cadena
  Cadena getPotencia(int indice);
  // metodo de suprimir las cadenas de long i de sufijos y prefijos y mostrarlos todos juntos
};

#endif  // CADENA_H
