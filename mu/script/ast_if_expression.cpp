#include <mu/script/ast_if_expression.h>

#include <mu/script/ast_definite_expression.h>

#include <gc_cpp.h>

mu::script::ast::if_expression::if_expression ():
predicate (new (GC) mu::script::ast::definite_expression),
true_branch (new (GC) mu::script::ast::definite_expression),
false_branch (new (GC) mu::script::ast::definite_expression)
{
}