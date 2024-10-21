#ifndef ESTADO_H 
#define ESTADO_H 

#include "simbolo.h"
#include <iostream>
#include <vector>
#include <map>

class Estado {
private:
  int id_;                                  // Nombre/identificador del estado
  bool is_acceptance_;                      // Definir si es estado de aceptación o no
  std::multimap<Simbolo, int> transitions_; // multimap de transiciones (simbolo -> destino)

public:
  /**
   * @brief Constante para representar epsilon-transiciones
   */
  static const Simbolo EPSILON; 

  /**
   * @brief Constructor de estados
   * 
   * @param id 
   * @param is_acceptance 
   */
  Estado(int id, bool is_acceptance);

  /**
   * @brief Añade una transición desde un estado con ese símbolo a un estado destino
   * 
   * @param simbolo 
   * @param next_state
   */
  void addTransition(const Simbolo& simbolo, int next_state);

  /**
   * @brief Getter de transiciones, acceso al multimap
   * 
   * @return const std::multimap<Simbolo, int>& 
   */
  const std::multimap<Simbolo, int>& getTransitions() const;

  /**
   * @brief Getter del ID de un estado
   * 
   * @return int 
   */
  int getId() const;

  /**
   * @brief Getter de si es estado de aceptación
   * 
   * @return true 
   * @return false 
   */
  bool getIsAcceptance() const;

  /**
   * @brief Getter de los siguientes estados a los que se puede transicionar con un símbolo
   * 
   * @param simbolo 
   * @return std::vector<int> 
   */
  std::vector<int> getNextStates(const Simbolo& simbolo) const;

  /**
   * @brief Sobrecarga de operador de igualdad para comparar si dos estados son iguales (mismo ID)
   * 
   * @param otro 
   * @return true 
   * @return false 
   */
  bool operator==(const Estado& otro) const;

  /**
   * @brief Sobrecarga del operador<< para imprimir estados de la forma: 
   * 
   * @param os 
   * @param estado 
   * @return std::ostream& 
   */
  friend std::ostream& operator<<(std::ostream& os, const Estado& estado);
};

#endif  // ESTADO_H
