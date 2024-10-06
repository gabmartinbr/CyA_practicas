#ifndef VARIABLE_H
#define VARIABLE_H

#include <iostream>
#include <string>

class Variable{
private:
  std::string name_;
  std::string type_;
  int line_number_;

public:
  Variable(const std::string& name, const std::string& type, int line_number);

  // getters
  std::string GetName() const;
  std::string GetType() const;
  int GetLineNumber() const;

  // convertir a string
  std::string ToString() const;

};

// sobrecarga de operador << para imprimir con formato [ Line linenum ] type : number
std::ostream& operator<<(std::ostream& os, const Variable& var);

#endif  // VARIABLE_H