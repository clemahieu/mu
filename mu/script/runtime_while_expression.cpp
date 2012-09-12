#include <mu/script/runtime_while_expression.h>

#include <mu/script/context.h>
#include <mu/core/check.h>
#include <mu/script/runtime_locals.h>
#include <mu/core/errors/error_target.h>

#include <mu/script/bool_c_node.h>

#include <gc_cpp.h>

#include <assert.h>

bool mu::script::runtime::while_expression::operator () (mu::script::context & context_a)
{
    auto valid (mu::core::check <mu::script::runtime::locals> (context_a));
    if (valid)
    {
        auto locals (static_cast <mu::script::runtime::locals *> (context_a.parameters (0)));
        for (auto i (predicate.begin ()), j (predicate.end ()); i != j && valid; ++i)
        {
            context_a.push (*i);
            context_a.push (locals);
            valid = context_a ();
            context_a.slide ();
        }
        if (context_a.locals_size () == 1)
        {
            for (auto i (body.begin ()), j (body.end ()); i != j && valid; ++i)
            {
                context_a.push (*i);
                context_a.push (locals);
                valid = context_a ();
                context_a.slide ();
            }
            if (context_a.locals_size () == 2)
            {
                context_a.push (new (GC) mu::script::bool_c::node (true));
                context_a.slide ();
                for (auto i (arguments.begin ()), j (arguments.end ()); i != j && valid; ++i)
                {
                    context_a.push (*i);
                    context_a.push (locals);
                    valid = context_a ();
                    context_a.slide ();
                }
                while (valid && static_cast <mu::script::bool_c::node *> (context_a.locals (2))->value)
                {
                    context_a.push (context_a.locals (0));
                    context_a.push (context_a.locals_begin () + 3, context_a.locals_end ());
                    valid = context_a ();
                    if (valid)
                    {
                        if (context_a.working_size () == 1)
                        {
                            auto bool_l (dynamic_cast <mu::script::bool_c::node *> (context_a.working (0)));
                            if (bool_l != nullptr)
                            {
                                context_a.locals (2) = bool_l;
                                context_a.drop();
                                if (bool_l->value)
                                {
                                    context_a.push (context_a.locals (1));
                                    context_a.push(context_a.locals_begin () + 3, context_a.locals_end ());
                                    valid = context_a ();
                                    if (valid)
                                    {
                                        if (context_a.working_size () == context_a.locals_size () - 3)
                                        {
                                            for (auto i (context_a.locals_begin () + 3),
                                                 j (context_a.locals_end()),
                                                 k (context_a.working_begin ()),
                                                 l (context_a.working_end ()); i != j; ++i)
                                            {
                                                assert (k != l);
                                                *i = *k;
                                            }
                                            context_a.drop ();
                                        }
                                        else
                                        {
                                            mu::stringstream message;
                                            message << U"Expecting body to return the same number of results as received.  Received: ";
                                            message << context_a.locals_size () - 3;
                                            message << U" body returned: ";
                                            message << context_a.working_size ();
                                            context_a.errors (message.str ());
                                            valid = false;
                                        }
                                    }
                                }
                            }
                            else
                            {
                                mu::stringstream message;
                                message << U"Expecting result to be a mu::script::bool_c::node, have: ";
                                message << context_a.working(0)->name ();
                                context_a.errors (message.str ());
                                valid = false;
                            }
                        }
                        else
                        {
                            mu::stringstream message;
                            message << U"Expecting predicate function to return one value, have: ";
                            message << context_a.working_size ();
                            context_a.errors (message.str ());
                            valid = false;
                        }
                    }
                    assert (static_cast <mu::script::bool_c::node *> (context_a.locals (2)) != nullptr);
                }
                assert (!valid || context_a.working_size () == 0);
                context_a.push (context_a.locals_begin() + 3, context_a.locals_end ());
            }
            else
            {
                mu::stringstream message;
                message << U"Expecting one value as body, have: ";
                message << context_a.locals_size () - 1;
                context_a.errors (message.str ());
                valid = false;
            }
        }
        else
        {
            mu::stringstream message;
            message << U"Expecting one value as predicate, have: ";
            message << context_a.locals_size ();
            context_a.errors (message.str ());
            valid = false;
        }
    }
    return valid;
}
