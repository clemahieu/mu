#include <mu/script/exec_operation.h>

#include <mu/core/errors/error_target.h>
#include <mu/script/string_node.h>
#include <mu/script/loads_operation.h>
#include <mu/script/parser_scope_node.h>
#include <mu/script/context.h>
#include <mu/core/check.h>
#include <mu/script/cluster_node.h>
#include <mu/script/runtime_routine.h>

#include <sstream>

#include <gc_cpp.h>

bool mu::script::exec::operation::operator () (mu::script::context & context_a)
{
	bool result (true);
	if (context_a.parameters_size () > 2)
	{
        auto scope (dynamic_cast <mu::script::parser_scope::node *> (context_a.parameters (0)));
        auto file (dynamic_cast <mu::script::string::node *> (context_a.parameters (1)));
        auto name (dynamic_cast <mu::script::string::node *> (context_a.parameters (2)));
        if (scope != nullptr)
        {
            if (file != nullptr)
            {
                if (name != nullptr)
                {
                    auto cluster (mu::script::loads::operation::core (context_a, scope, file));
                    if (cluster != nullptr)
                    {
                        auto routine (cluster->routines.find (name->string));
                        if (routine != cluster->routines.end ())
                        {
                            context_a.push (routine->second);
                            for (auto i (context_a.parameters_begin () + 3), j (context_a.parameters_end ()); i != j; ++i)
                            {
                                context_a.push (*i);
                            }
                            result = context_a ();
                        }
                        else
                        {
                            mu::stringstream message;
                            message << U"Cluster has no routines";
                            context_a.errors (message.str ());
                            result = false;
                        }
                    }
                    else
                    {
                        result = false;
                    }
                }
                else
                {
                    mu::core::type_fail (context_a.errors, typeid (mu::script::string::node), context_a.working (2), 2);
                }
            }
            else
            {
                mu::core::type_fail (context_a.errors, typeid (mu::script::string::node), context_a.working (1), 1);
            }
        }
        else
        {
            mu::core::type_fail (context_a.errors, typeid (mu::script::parser_scope::node), context_a.working (0), 0);
        }
	}
	else
	{
		mu::stringstream message;
		message << U"Operation ";
		message << name ();
		message << U" requires at least two arguments";
		context_a.errors (message.str ());
		result = false;
	}
	return result;
}

mu::string mu::script::exec::operation::name ()
{
	return mu::string (U"mu::script::exec::operation");
}