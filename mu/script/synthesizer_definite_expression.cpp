#include <mu/script/synthesizer_definite_expression.h>

#include <mu/script/synthesizer_routine.h>
#include <mu/core/errors/error_target.h>
#include <mu/script/ast_definite_expression.h>
#include <mu/script/runtime_definite_expression.h>
#include <mu/script/ast_routine.h>
#include <mu/script/ast_reference.h>
#include <mu/script/runtime_fixed.h>
#include <mu/script/runtime_selection.h>
#include <mu/script/runtime_reference.h>
#include <mu/script/ast_parameter.h>
#include <mu/script/runtime_parameter.h>
#include <mu/script/runtime_routine.h>
#include <mu/script/ast_routine.h>
#include <mu/script/synthesizer_cluster.h>
#include <mu/script/ast_if_expression.h>

#include <gc_cpp.h>

#include <assert.h>

mu::script::synthesizer::definite_expression::definite_expression (mu::script::synthesizer::routine & routine_a, mu::script::ast::definite_expression * expression_a)
{
    auto expression_c (recurse_expression (routine_a, expression_a));
    routine_a.routine_m->expressions.push_back (expression_c);
}

void mu::script::synthesizer::definite_expression::recurse (mu::script::synthesizer::routine & routine_a, mu::core::node * node_a, mu::script::runtime::definite_expression * expression_a)
{
    auto definite_expression_l (dynamic_cast <mu::script::ast::definite_expression *> (node_a));
    auto if_expression (dynamic_cast <mu::script::ast::if_expression *> (node_a));
    auto reference (dynamic_cast <mu::script::ast::reference *> (node_a));
    auto parameter_l (dynamic_cast <mu::script::ast::parameter *> (node_a));
    auto routine_l (dynamic_cast <mu::script::ast::routine *> (node_a));
    if (definite_expression_l != nullptr)
    {
        auto expression_c (recurse_expression (routine_a, definite_expression_l));
        expression_a->dependencies.push_back (new (GC) mu::script::runtime::reference (expression_c));
        routine_a.routine_m->expressions.push_back (expression_c);
    }
    else if (reference != nullptr)
    {
        assert (dynamic_cast <mu::script::ast::definite_expression *> (reference->expression) != nullptr);
        auto expression_c (recurse_expression (routine_a, static_cast <mu::script::ast::definite_expression *> (reference->expression)));
        expression_a->dependencies.push_back (new (GC) mu::script::runtime::selection (expression_c, reference->position));
        routine_a.routine_m->expressions.push_back (expression_c);
    }
    else if (parameter_l != nullptr)
    {
        expression_a->dependencies.push_back (new (GC) mu::script::runtime::parameter (parameter_l->position));
    }
    else if (routine_l != nullptr)
    {
        auto existing (routine_a.cluster.routines.find (routine_l));
        if (existing == routine_a.cluster.routines.end ())
        {
            mu::script::synthesizer::routine routine_c (routine_a.errors, routine_a.cluster, routine_l);
            expression_a->dependencies.push_back (new (GC) mu::script::runtime::fixed (routine_c.routine_m));
        }
        else
        {
            expression_a->dependencies.push_back (new (GC) mu::script::runtime::fixed (existing->second));
        }
    }
    /*else if (if_expression != nullptr)
    {
        assert (false);
    }*/
    else
    {
        expression_a->dependencies.push_back (new (GC) mu::script::runtime::fixed (node_a));
    }
}

auto mu::script::synthesizer::definite_expression::recurse_expression (mu::script::synthesizer::routine & routine_a, mu::script::ast::definite_expression * expression_a) -> mu::script::runtime::definite_expression *
{
    mu::script::runtime::definite_expression * result (nullptr);
    if (routine_a.current_cycle.find (expression_a) != routine_a.current_cycle.end ())
    {
        routine_a.errors (U"Routine has a cycle");
    }
    else
    {
        routine_a.current_cycle.insert (expression_a);
        auto existing (routine_a.already_parsed.find (expression_a));
        if (existing == routine_a.already_parsed.end ())
        {            
            auto expression_l (new (GC) mu::script::runtime::definite_expression);
            for (auto i (expression_a->nodes.begin ()), j (expression_a->nodes.end ()); i != j; ++i)
            {
                auto current (*i);
                recurse (routine_a, current, expression_l);
            }
            result = expression_l;
            routine_a.already_parsed.insert (decltype (routine_a.already_parsed)::value_type (expression_a, expression_l));
        }
        else
        {
            result = existing->second;
        }
        routine_a.current_cycle.erase (expression_a);
    }
    return result;
}