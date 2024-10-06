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
  bool has_main_func_ = false;

public:
  CodeBlock();
  void AddComment(const Comment& comment);
  void AddLoop(const Loop& loop);
  void AddVariable(const Variable& variable);
  void SetHasMain(bool has_main);

  const std::vector<Comment>& GetComments() const;
  const std::vector<Variable>& GetVariables() const;
  const std::vector<Loop>& GetLoops() const;
  bool HasMain() const;



};



#endif  // CODE_BLOCK_H