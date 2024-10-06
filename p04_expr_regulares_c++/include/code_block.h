#ifndef CODE_BLOCK
#define CODE_BLOCK

#include <vector>
#include "comment.h"
#include "loop.h"
#include "variable.h"

class CodeBlock {
private:
  std::vector<Comment> comments_;
  std::vector<Loop> loops_;
  std::vector<Variable> variables_;
  Comment description_;
  bool has_description_;
  bool has_main_func_;

public:
  CodeBlock();
  void AddComment(const Comment& comment);
  void AddLoop(const Loop& loop);
  void AddVariable(const Variable& variable);

  void SetHasMain(bool has_main);
  void SetDescription(const Comment& comm);

  const std::vector<Comment>& GetComments() const;
  const std::vector<Variable>& GetVariables() const;
  const std::vector<Loop>& GetLoops() const;
  bool HasMain() const;
  bool HasDescription() const;   
  const Comment& GetDescription() const; 



};



#endif  // CODE_BLOCK_H