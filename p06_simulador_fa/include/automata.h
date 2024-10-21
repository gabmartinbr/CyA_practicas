#ifndef AUTOMATA_H 
#define AUTOMATA_H 

#include "estado.h"
#include "alfabeto.h"
#include <set>

class Automata {
private:
  std::map<int, Estado> states_; // map de estados del automata
  Alfabeto alfabeto_; // alfabeto del automata
  std::set<int> acceptance_states_; // estados de aceptacion del automata

public:
};

#endif  // AUTOMATA_H
