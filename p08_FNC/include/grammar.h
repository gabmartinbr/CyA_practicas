#ifndef GRAMMAR_H
#define GRAMMAR_H

#include "simbolo.h"
#include "alfabeto.h"
#include "production.h"
#include <set>
#include <vector>

class Grammar {
private:
  Alfabeto terminals_;
  std::set<Simbolo> no_terminals_;
  Simbolo start_symbol_;
  std::vector<Production> productions;

public:
  /**
   * @brief Constructor de un objeto gramatica
   * 
   * @param terminals 
   * @param no_terminals 
   * @param start_symbol 
   * @param productions 
   */
  Grammar(const Alfabeto& terminals,
          const std::set<Simbolo>& no_terminals,
          const Simbolo& start_symbol,
          const std::vector<Production>& productions);
 
  /**
   * @brief comprobacion de si la gramatica tiene prod vacias
   * 
   * @return true 
   * @return false 
   */
  bool hasEmptyProd() const;
  
  /**
   * @brief comprobacion de si la gramatica tiene prod unitarias
   * 
   * @return true 
   * @return false 
   */
  bool hasUnitProd() const;

  /**
   * @brief metodo que realiza la conversion a cnf
   * 
   */
  void converterCNF();
};

/**
 * @brief sobrecarga del operador << para la escritura de gramatica
 * 
 * @param os 
 * @param grammar 
 * @return std::ostream& 
 */
std::ostream& operator<<(std::ostream& os, const Grammar& grammar);

#endif  // GRAMMAR_H
