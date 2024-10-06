#include "variable.h"

Variable::Variable(const std::string& name, const std::string& type, int line_number) 
  : name_(name), type_(type), line_number_(line_number) {}

// getters
std::string Variable::GetName() const {
  return name_;
}

std::string Variable::GetType() const {
  return type_;
}

int Variable::GetLineNumber() const {
  return line_number_;
}

// sobrecarga del operador << 
std::ostream& operator<<(std::ostream& os, const Variable& var) {
  os << "[ Line " << var.GetLineNumber() << "] " << var.GetType() << " : " << var.GetName();
  return os;
}