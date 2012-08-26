#include <mu/llvm_/synthesizer_expression.h>

#include <mu/llvm_/ast_expression.h>
#include <mu/llvm_/ctx.h>
#include <mu/llvm_/synthesizer_routine.h>
#include <mu/core/errors/error_target.h>
#include <mu/llvm_/value_node.h>
#include <mu/llvm_/operation.h>
#include <mu/core/node_list.h>
#include <mu/llvm_/ast_parameter.h>
#include <mu/llvm_/function_node.h>
#include <mu/llvm_/argument_node.h>

#include <llvm/Function.h>

#include <gc_cpp.h>

mu::llvm_::synthesizer::expression::expression (mu::llvm_::ctx & ctx_a, mu::core::errors::error_target & errors_a, mu::llvm_::synthesizer::routine & routine_a, mu::llvm_::ast::expression * expression_a)
{
    mu::llvm_::operation * operation;
    {
        auto i (expression_a->nodes.begin ());
        auto j (expression_a->nodes.end ());
        if (i != j)
        {
            operation = dynamic_cast <mu::llvm_::operation *> (*i);
            ++i;
            for (; i != j; ++i)
            {
                auto argument_l (dynamic_cast <mu::llvm_::ast::parameter *> (*i));
                if (argument_l == nullptr)
                {
                    ctx_a.working.push_back (*i);
                }
                else
                {
                    ctx_a.working.push_back (routine_a.arguments [argument_l->position]);
                }
            }
        }
        else
        {
            errors_a (U"Expression has no nodes");
        }
    }    
    if (operation != nullptr)
    {
        auto valid ((*operation) (ctx_a));
        if (valid)
        {
            if (ctx_a.working.size () == 1)
            {
                routine_a.already_parsed.insert (decltype (routine_a.already_parsed)::value_type (expression_a, ctx_a.working [0]));
            }
            else
            {
                auto nodes (new (GC) mu::core::node_list);
                for (auto i (ctx_a.working.begin ()), j (ctx_a.working.end ()); i != j; ++i)
                {
                    nodes->nodes.push_back (*i);
                }
                routine_a.already_parsed.insert (decltype (routine_a.already_parsed)::value_type (expression_a, nodes));
            }
        }
        else
        {
            errors_a (U"Evaluating expression operation failed");
        }
    }
    else
    {
        errors_a (U"Value is not an operation");
    }
}