#ifndef LOOP_H
#define LOOP_H

#include <string>
#include <iostream>
#include <regex>

class Loop{
private:
  int line_number_;
  std::string type_;

public:
  Loop(int line_counter, std::smatch& match);

  // Getters
  int GetLineNumber() const;
  std::string GetType() const;

};

std::ostream& operator<<(std::ostream& os, const Loop& loop);


#endif  // LOOP_H