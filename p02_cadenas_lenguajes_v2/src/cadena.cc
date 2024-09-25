// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 2: Cadenas y lenguajes
// Autor: Gabriel Martín Broock
// Correo: alu0101539157@ull.edu.es
// Fecha: 22/09/2024
// Archivo cadena.cc: clase Cadena.
// Contiene la implementación de la clase Cadena 
// para poder usar objetos tipo cadena (vector de símbolos) y 
// realizar operaciones sobre ellos.
// Referencias:
// Enlaces de interés /
// Historial de revisiones:
// 19/09/2024 - Creación (primera versión) del código

#include "cadena.h"

// definición de cadena vacía
const Simbolo Cadena::CAD_VACIA = Simbolo('&');

/**
 * @brief Constructor por defecto de la clase Cadena.
 */
Cadena::Cadena() {}

/**
 * @brief Constructor de la clase Cadena a partir de un vector de símbolos y un alfabeto.
 * 
 * @param simbolos Vector de símbolos que forman la cadena.
 * @param alfabeto Alfabeto al que pertenecen los símbolos.
 */
Cadena::Cadena(const std::vector<Simbolo>& simbolos, const Alfabeto& alfabeto)
  : cadena_(simbolos), alfabeto_(alfabeto) {}

/**
 * @brief Getter para obtener la cadena.
 * 
 * @return const std::vector<Simbolo>& Referencia constante al vector de símbolos de la cadena.
 */
const std::vector<Simbolo>& Cadena::getCadena() const {
  return cadena_;
}

/**
 * @brief Getter para obtener el alfabeto de la cadena.
 * 
 * @return const Alfabeto& Referencia constante al alfabeto de la cadena.
 */
const Alfabeto& Cadena::getAlfabeto() const {
  return alfabeto_;
}

/**
 * @brief Método para añadir símbolos a la cadena.
 * 
 * @param simbolo El símbolo a añadir a la cadena.
 */
void Cadena::addSimbolo(const Simbolo& simbolo) {
  cadena_.push_back(simbolo);
}

/**
 * @brief Método para obtener los prefijos de la cadena.
 * 
 * @return std::set<Cadena> Conjunto de prefijos de la cadena.
 */
std::set<Cadena> Cadena::getPrefijos() const {
  std::set<Cadena> prefijos;  // conjunto de prefijos
  Cadena simbolosPrefijo; // almacenar cada símbolo de cada prefijo
  
  // Añadir la cadena vacía como primer prefijo
  prefijos.insert(Cadena());  // insertar la cadena vacía (&)

  for (size_t i = 0; i < cadena_.size(); i++) { // recorrer cadena desde el principio
    simbolosPrefijo.addSimbolo(cadena_[i]); // añadir símbolo a la cadena de prefijo
    prefijos.insert(simbolosPrefijo); // añadir cadena prefijos al conjunto prefijos
  }

  return prefijos;
}

/**
 * @brief Método para obtener los sufijos de la cadena.
 * 
 * @return std::set<Cadena> Conjunto de sufijos de la cadena.
 */
std::set<Cadena> Cadena::getSufijos() const {
    std::set<Cadena> sufijos; // conjunto de sufijos
    sufijos.insert(Cadena()); // añadir el sufijo vacío (&)

    // Crear sufijos comenzando desde cada posición
    for (size_t i = 0; i < cadena_.size(); i++) {
        Cadena sufijo;  // sufijo temporal
        // Agregar los símbolos desde la posición actual hasta el final
        for (size_t j = i; j < cadena_.size(); j++) {
            sufijo.addSimbolo(cadena_[j]); // añadir símbolo al sufijo
        }
        sufijos.insert(sufijo); // añadir sufijo al conjunto
    }

    return sufijos;
}

/**
 * @brief Método que devuelve la cadena inversa.
 * 
 * @return Cadena Cadena invertida.
 */
Cadena Cadena::getInversa() const {
  std::vector<Simbolo> simbolosInversa; // vector de símbolos para construir cadena inversa
  for (int i = cadena_.size() - 1; i >= 0; i--) { // recorrer cadena desde el final
    simbolosInversa.push_back(cadena_[i]);  // agregar símbolo en orden inverso al vector de símbolos
  }
  Cadena inversa(simbolosInversa, getAlfabeto());  // crear cadena inversa y su alfabeto
  return inversa;
}

/**
 * @brief Método que devuelve la longitud de la cadena.
 * 
 * @return size_t Número de símbolos en la cadena.
 */
size_t Cadena::getLongitud() const {
  return cadena_.size();
}

/**
 * @brief Sobrecarga del operador < para el uso de cadenas ordenadas en un conjunto.
 * 
 * @param otra Otra cadena con la que se compara.
 * @return true Si esta cadena es menor que la otra.
 * @return false Si esta cadena no es menor que la otra.
 */
bool Cadena::operator<(const Cadena& otra) const {
    if (cadena_.size() < otra.cadena_.size()) {
      return true;
    } else if (cadena_.size() > otra.cadena_.size()) {
      return false;
    }
    for (size_t i = 0; i < cadena_.size(); i++) {
      if (cadena_[i].getSimbolo() < otra.cadena_[i].getSimbolo()) {
        return true;
      } else if (cadena_[i].getSimbolo() > otra.cadena_[i].getSimbolo()) {
        return false;
      }
    }
    return false;
}

/**
 * @brief Sobrecarga del operador == para comparar cadenas
 * 
 * @param otra Otra cadena con la que se compara.
 * @return true Si esta cadena es igual que la otra.
 * @return false Si esta cadena no es igual que la otra.
 */
bool Cadena::operator==(const Cadena& otra) const {
    // Comparar el tamaño de ambas cadenas
    if (this->getLongitud() != otra.getLongitud()) {
        return false; // Si no son del mismo tamaño, no son iguales
    }
    
    // Comparar los símbolos de ambas cadenas
    return this->getCadena() == otra.getCadena(); // Comparar los vectores de símbolos
}

/**
 * @brief Sobrecarga del operador + para concatenar cadenas
 * 
 * @param os Flujo de salida.
 * @param otra cadena a concatenar
 * @return std::ostream& Referencia al flujo de salida.
 */
Cadena Cadena::operator+(const Cadena& otra) const {
    Cadena resultado;

    // Agregar los símbolos de la cadena actual
    for (const auto& simbolo : this->getCadena()) {
        resultado.addSimbolo(simbolo);
    }

    // Agregar los símbolos de la otra cadena
    for (const auto& simbolo : otra.getCadena()) {
        resultado.addSimbolo(simbolo);
    }

    return resultado; // Retornar la nueva cadena resultante
}

/**
 * @brief Sobrecarga del operador << para mostrar la cadena de forma legible.
 * 
 * @param os Flujo de salida.
 * @param cadena Objeto Cadena a mostrar.
 * @return std::ostream& Referencia al flujo de salida.
 */
std::ostream& operator<<(std::ostream& os, const Cadena& cadena) {
  for (const auto& simbolo : cadena.cadena_) {  // recorrer cada símbolo de la cadena
    os << simbolo.getSimbolo();
  }
  return os;
}

// metodo de si una cadena es palindroma y poner true o false en archivo
bool Cadena::isPalindroma(){
  return this->getCadena() == this->getInversa().getCadena();
}

// metodo de potencia de una cadena
Cadena Cadena::getPotencia(int indice) {
  Cadena potencia;
  if (indice <= 0) {
    return potencia;
  }
  for (int i = 0; i < indice; i++) {
    for (size_t j = 0; j < this->getLongitud(); j++) {
      potencia.addSimbolo(this->getCadena()[j]);
    }
  }

  return potencia;
}