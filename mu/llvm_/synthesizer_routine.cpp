#include <mu/llvm_/synthesizer_routine.h>

#include <mu/llvm_/synthesizer_expression.h>
#include <mu/llvm_/ast_routine.h>

mu::llvm_::synthesizer::routine::routine (mu::core::errors::error_target & errors_a, mu::llvm_::ast::routine * routine_a)
{
    mu::llvm_::synthesizer::expression expression (errors_a, routine_a->body);
}