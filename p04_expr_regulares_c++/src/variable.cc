#include "variable.h"

Variable::Variable(int line_counter, std::smatch& match) {
  line_number_ = line_counter;

  // El primer grupo (match[1]) es el tipo de variable, el segundo (match[2]) es el nombre
  if (match.size() >= 2) {
    type_ = match[1].str();
    name_ = match[2].str();
    value_ = match[3].str();
  } else {
    std::cerr << "Error: no se pudo extraera el tipo y nombre de la variable" << match.size() << line_counter << std::endl;
  }
}


void Variable::SetAsign() {
  is_asign_ = true;
}

bool Variable::GetAsign() {
  return is_asign_;
}

// getters
std::string Variable::GetName() const {
  return name_;
}

std::string Variable::GetType() const {
  return type_;
}

std::string Variable::GetValue() const {
  return value_;
}

int Variable::GetLineNumber() const {
  return line_number_;
}

// sobrecarga del operador << 
std::ostream& operator<<(std::ostream& os, const Variable& var) {
  os << "[Line " << var.GetLineNumber() << "] " << var.GetType() << ": " << var.GetName() << var.GetValue();
  return os;
}