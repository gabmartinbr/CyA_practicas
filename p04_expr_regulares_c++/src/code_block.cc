#include "code_block.h"

CodeBlock::CodeBlock() {}

// Agregar una variable
void CodeBlock::AddVariable(const Variable& var) {
    variables_.push_back(var);
}

// Agregar un comentario
void CodeBlock::AddComment(const Comment& comment) {
    comments_.push_back(comment);
}

// Agregar un bucle
void CodeBlock::AddLoop(const Loop& loop) {
    loops_.push_back(loop);
}

// Establecer si tiene función `main`
void CodeBlock::SetHasMain(bool has_main) {
    has_main_func_ = has_main;
}

// Establecer el comentario como descripción
void CodeBlock::SetDescription(const Comment& comment) {
    description_ = comment;
    has_description_ = true;
}

// Obtener las variables
const std::vector<Variable>& CodeBlock::GetVariables() const {
    return variables_;
}

// Obtener los comentarios
const std::vector<Comment>& CodeBlock::GetComments() const {
    return comments_;
}

// Obtener los bucles
const std::vector<Loop>& CodeBlock::GetLoops() const {
    return loops_;
}

// Verificar si hay función `main`
bool CodeBlock::HasMain() const {
    return has_main_func_;
}

// Verificar si hay una descripción
bool CodeBlock::HasDescription() const {
    return has_description_;
}

// Obtener la descripción
const Comment& CodeBlock::GetDescription() const {
    return description_;
}

