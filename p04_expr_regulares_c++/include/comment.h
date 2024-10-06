#ifndef COMMENT_H
#define COMMENT_H

#include <string>
#include <iostream>

class Comment {
private:
  int ini_line_;
  int end_line_;
  std::string content_;
  std::string type_;

public:
  Comment(int ini_line, int end_line, const std::string& content, std::string& type);

  // getters
  int GetIniLine() const;
  int GetEndLine() const;
  std::string GetContent() const;
  std::string GetType() const;
};

std::ostream& operator<<(std::ostream& os, const Comment& comm);

#endif  // COMMENT_H
