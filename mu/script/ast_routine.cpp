#include <mu/script/ast_routine.h>

#include <mu/script/ast_expression.h>

mu::script::ast::routine::routine ():
body (new mu::script::ast::expression)
{
}