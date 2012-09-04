#include <mu/script/ast_routine.h>

#include <mu/script/ast_definite_expression.h>

mu::script::ast::routine::routine ():
body (new mu::script::ast::definite_expression)
{
}