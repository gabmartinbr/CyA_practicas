#ifndef GRAMMAR_H
#define GRAMMAR_H

#include "simbolo.h"
#include "cadena.h"
#include "alfabeto.h"
#include <fstream>
#include <sstream>
#include <map>
#include <set>
#include <vector>
#include <algorithm>

class Grammar {
private:
  Alfabeto terminals_;
  std::set<Simbolo> no_terminals_;
  Simbolo start_symbol_;
  std::map<Simbolo, std::set<Cadena>> productions_;
  std::map<Simbolo, Simbolo> terminalToNonTerminal;  // Mapa de terminal a no terminal


public:
  /**
   * @brief Construct a new Grammar object
   * 
   * @param terminals 
   * @param no_terminals 
   * @param start_symbol 
   * @param productions 
   */
  Grammar();
  Grammar(const Alfabeto& terminals,
          const std::set<Simbolo>& no_terminals,
          const Simbolo& start_symbol,
          const std::map<Simbolo, std::set<Cadena>>& productions);
 
Simbolo getStartSymbol() const;

  bool isNonTerminal(const Simbolo& simbol) const;
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

  void deleteUnitProd();

  void deleteEmptyProd();

  /**
   * @brief metodo que realiza la conversion a cnf
   * 
   */
  void converterCNF();
  void addTerminal(const Simbolo &terminal);
  void addNonTerminal(const Simbolo &nonTerminal);
  void replaceTerminals();
  void decomposeLongProductions();
  Simbolo generateNewNonTerminal();
  void addProduction(const Simbolo &nonTerminal, const Cadena &production);
  void writeGrammar(std::string filename);
  void readGrammar(std::ifstream &inputFile);
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
