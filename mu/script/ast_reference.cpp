#include <mu/script/ast_reference.h>

mu::script::ast::reference::reference (mu::script::ast::expression * expression_a, size_t position_a):
expression (expression_a),
position (position_a)
{
}