#include <mu/llvm_/synthesizer_expression.h>

#include <mu/llvm_/ast_expression.h>
#include <mu/llvm_/ctx.h>
#include <mu/llvm_/synthesizer_routine.h>
#include <mu/core/errors/error_target.h>

mu::llvm_::synthesizer::expression::expression (mu::llvm_::ctx & ctx_a, mu::core::errors::error_target & errors_a, mu::llvm_::synthesizer::routine & routine_a, mu::llvm_::ast::expression * expression_a)
{
    
    {
        auto i (expression_a->nodes.begin ());
        auto j (expression_a->nodes.end ());
        if (i != j)
        {
            auto operation (*i);
            ++i;
            for (; i != j; ++i)
            {
                ctx_a
            }
            routine_a.already_parsed.insert (value);
        }
        else
        {
            errors_a (U"No mu::llvm_::operation");
        }
    }
}