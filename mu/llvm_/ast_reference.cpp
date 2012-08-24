#include <mu/llvm_/ast_reference.h>

mu::llvm_::ast::reference::reference (mu::llvm_::ast::expression * expression_a, size_t position_a):
expression (expression_a),
position (position_a)
{
}