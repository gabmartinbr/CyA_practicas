#ifndef LOOP_H
#define LOOP_H

#include <string>
#include <iostream>

class Loop{
private:
  int line_number_;
  std::string type_;

public:
  Loop(int line_number, const std::string& type);

  // Getters
  int GetLineNumber() const;
  std::string GetType() const;

};

std::ostream& operator<<(std::ostream& os, const Loop& loop);


#endif  // LOOP_H