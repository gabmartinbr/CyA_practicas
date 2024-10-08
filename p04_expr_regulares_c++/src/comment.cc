#include "comment.h"

Comment::Comment() : ini_line_(0), end_line_(0), content_(""), type_("") {}

Comment::Comment(int ini_line, int end_line, const std::string& content, const std::string& type)
  : ini_line_(ini_line), end_line_(end_line), content_(content), type_(type) {}

Comment::Comment(int ini_line, const std::string& content, const std::string& type)
  : ini_line_(ini_line), content_(content), type_(type) {}

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

bool Comment::GetIsDescription() const {
  return is_description_;
}

void Comment::SetIsDescription() {
  is_description_ = true;
}

std::ostream& operator<<(std::ostream& os, const Comment& comm) {
  if (comm.GetIsDescription() == false) { 
    os << "[ Line " << comm.GetIniLine() << " - " << comm.GetEndLine() << "] " 
        << comm.GetType() << ": " << comm.GetContent();
  }
  if (comm.GetIsDescription() == true) {
    os << "[ Line " << comm.GetIniLine() << " - " << comm.GetEndLine() << "] DESCRIPTION";
  }
  return os;
}
