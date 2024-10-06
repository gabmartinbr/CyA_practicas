#include "comment.h"

Comment::Comment(int ini_line, int end_line, const std::string& content, std::string& type)
  : ini_line_(ini_line), end_line_(end_line), content_(content), type_(type) {}

// getters
int Comment::GetIniLine() const{
  return ini_line_;
}

int Comment::GetEndLine() const{
  return end_line_;
}

std::string Comment::GetContent() const {
  return content_;
}

std::string Comment::GetType() const {
  return type_;
}

std::ostream& operator<<(std::ostream& os, const Comment& comm) {
  os << "[ Line " << comm.GetIniLine() << " - " << comm.GetEndLine() << "] " 
       << comm.GetType() << ": " << comm.GetContent();
    return os;
}
