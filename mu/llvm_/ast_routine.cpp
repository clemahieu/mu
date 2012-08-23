#include <mu/llvm_/ast_routine.h>

#include <mu/llvm_/ast_expression.h>

#include <gc_cpp.h>

mu::llvm_::ast::routine::routine ():
body (new (GC) mu::llvm_::ast::expression)
{
}