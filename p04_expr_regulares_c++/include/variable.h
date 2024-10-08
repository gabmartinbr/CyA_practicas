#ifndef VARIABLE_H
#define VARIABLE_H

#include <iostream>
#include <string>
#include <regex>

class Variable{
private:
  std::string name_;
  std::string type_;
  std::string value_;
  int line_number_;

public:
  Variable(int line_counter, std::smatch& match);

  // getters
  std::string GetName() const;
  std::string GetType() const;
  std::string GetValue() const;

  int GetLineNumber() const;

  // convertir a string
  std::string ToString() const;

};

// sobrecarga de operador << para imprimir con formato [ Line linenum ] type : number
std::ostream& operator<<(std::ostream& os, const Variable& var);

#endif  // VARIABLE_H