#include <mu/script/synthesizer_expression.h>

#include <mu/script/synthesizer_routine.h>
#include <mu/core/errors/error_target.h>
#include <mu/script/ast_expression.h>
#include <mu/script/runtime/expression.h>
#include <mu/script/ast_routine.h>
#include <mu/script/ast_reference.h>
#include <mu/script/runtime/fixed.h>
#include <mu/script/runtime/selection.h>
#include <mu/script/runtime/reference.h>
#include <mu/script/ast_parameter.h>
#include <mu/script/runtime/parameter.h>
#include <mu/script/runtime/routine.h>
#include <mu/script/ast_routine.h>
#include <mu/script/synthesizer_cluster.h>

#include <gc_cpp.h>

#include <assert.h>

mu::script::synthesizer::expression::expression (mu::script::synthesizer::routine & routine_a, mu::script::ast::expression * expression_a):
expression_m (new (GC) mu::script::runtime::expression)
{
    for (auto i (expression_a->nodes.begin ()), j (expression_a->nodes.end ()); i != j; ++i)
    {
        auto current (*i);
        auto expression_l (dynamic_cast <mu::script::ast::expression *> (current));
        auto reference (dynamic_cast <mu::script::ast::reference *> (current));
        auto parameter_l (dynamic_cast <mu::script::ast::parameter *> (current));
        auto routine_l (dynamic_cast <mu::script::ast::routine *> (current));
        if (expression_l != nullptr)
        {
            auto expression_c (recurse (routine_a, expression_l));
            expression_m->dependencies.push_back(new (GC) mu::script::runtime::reference (expression_c));
        }
        else if (reference != nullptr)
        {
            auto expression_c (recurse (routine_a, reference->expression));
            expression_m->dependencies.push_back(new (GC) mu::script::runtime::selection (expression_c, reference->position));
        }
        else if (parameter_l != nullptr)
        {
            expression_m->dependencies.push_back (new (GC) mu::script::runtime::parameter (parameter_l->position));
        }
        else if (routine_l != nullptr)
        {
            auto existing (routine_a.cluster.routines.find (routine_l));
            if (existing == routine_a.cluster.routines.end ())
            {
                mu::script::synthesizer::routine routine_c (routine_a.errors, routine_a.cluster, routine_l);
                expression_m->dependencies.push_back (new (GC) mu::script::runtime::fixed (routine_c.routine_m));
            }
            else
            {
                expression_m->dependencies.push_back (new (GC) mu::script::runtime::fixed (existing->second));
            }
        }
        else
        {
            expression_m->dependencies.push_back (new (GC) mu::script::runtime::fixed (current));
        }
    }
    routine_a.already_parsed.insert (decltype (routine_a.already_parsed)::value_type (expression_a, expression_m));
    routine_a.routine_m->expressions.push_back (expression_m);
}

auto mu::script::synthesizer::expression::recurse (mu::script::synthesizer::routine & routine_a, mu::script::ast::expression *expression_a) -> mu::script::runtime::expression *
{
    mu::script::runtime::expression * result (nullptr);
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
            mu::script::synthesizer::expression expression_l (routine_a, expression_a);
            result = expression_l.expression_m;
        }
        else
        {
            result = existing->second;
        }
        routine_a.current_cycle.erase (expression_a);
    }
    return result;
}