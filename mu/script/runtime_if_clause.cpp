#include <mu/script/runtime_if_clause.h>

#include <mu/core/check.h>
#include <mu/script/runtime_locals.h>
#include <mu/script/context.h>
#include <mu/script/runtime_expression.h>
#include <mu/core/errors/error_target.h>
#include <mu/script/bool_c_node.h>

bool mu::script::runtime::if_clause::operator () (mu::script::context & context_a)
{
    bool valid (mu::core::check <mu::script::runtime::locals> (context_a));
    if (valid)
    {
        context_a.push (predicate);
        context_a.push (context_a.parameters(0));
        valid = context_a ();
        if (valid)
        {
            if (context_a.working_size() == 1)
            {
                auto value (dynamic_cast <mu::script::bool_c::node *> (context_a.working(0)));
                if (value != nullptr)
                {
                    context_a.drop ();
                    if (value->value)
                    {
                        context_a.push (true_branch);
                        context_a.push (context_a.parameters(0));
                        valid = context_a ();
                    }
                    else
                    {
                        context_a.push (false_branch);
                        context_a.push (context_a.parameters(0));
                        valid = context_a ();
                    }
                }
                else
                {
                    mu::stringstream message;
                    message << U"Predicate function is expected to return a bool, have: ";
                    message << context_a.working (0)->name();
                    context_a.errors (message.str ());
                }
            }
            else
            {
                mu::stringstream message;
                message << U"Predicate function is expected to return 1 value, have";
                message << context_a.working_size ();
                context_a.errors (message.str ());
            }
        }
    }
    return valid;
}