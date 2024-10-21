#include "estado.h"

// Definición de la constante EPSILON (puedes definirla como un símbolo específico)
const Simbolo Estado::EPSILON = Simbolo('\0'); // O el símbolo que elijas para epsilon

// Constructor
Estado::Estado(int id, bool is_acceptance)
    : id_(id), is_acceptance_(is_acceptance) {}

// Añade una transición
void Estado::addTransition(const Simbolo& simbolo, int next_state) {
    transitions_.insert({simbolo, next_state}); // Inserta la transición en el multimap
}

// Getter de transiciones
const std::multimap<Simbolo, int>& Estado::getTransitions() const {
    return transitions_; // Devuelve el multimap de transiciones
}

// Getter del ID de un estado
int Estado::getId() const {
    return id_; // Devuelve el ID del estado
}

// Getter de si es estado de aceptación
bool Estado::getIsAcceptance() const {
    return is_acceptance_; // Devuelve si es un estado de aceptación
}

// Obtener los siguientes estados dado un símbolo
std::vector<int> Estado::getNextStates(const Simbolo& simbolo) const {
    std::vector<int> result;
    auto range = transitions_.equal_range(simbolo); // Obtiene el rango de estados para el símbolo dado
    for (auto it = range.first; it != range.second; ++it) {
        result.push_back(it->second); // Agrega cada estado asociado al símbolo
    }
    return result; // Devuelve el vector de estados
}

// Sobrecarga del operador==
bool Estado::operator==(const Estado& otro) const {
    return id_ == otro.id_; // Compara si los IDs son iguales
}

// Sobrecarga del operador<< para imprimir el estado
std::ostream& operator<<(std::ostream& os, const Estado& estado) {
    os << estado.id_ << " --- " 
       << (estado.is_acceptance_ ? "Accepted" : "Rejected");
    return os; // Devuelve el flujo de salida
}
