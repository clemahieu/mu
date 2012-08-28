#include <mu/script/run_operation.h>

#include <mu/core/errors/error_target.h>
#include <mu/script/string_node.h>
#include <mu/io/lexer_istream_input.h>
#include <mu/io/source.h>
#include <mu/script/parser_scope_node.h>
#include <mu/core/check.h>
#include <mu/script/context.h>

#include <boost/filesystem.hpp>
#include <boost/bind.hpp>

#include <sstream>

bool mu::script::run::operation::operator () (mu::script::context & context_a)
{
    assert (false);/*
	bool result (true);
	if (context_a.parameters_size () > 0)
	{
		auto file (dynamic_cast <mu::script::string::node *> (context_a.parameters (0)));
        if (file != nullptr)
        {
            mu::script::load::operation load;
            auto ast (load.core (context_a, file));
            if (! context_a ())
            {
                mu::script::analyzer::operation analyzer;
                auto cluster (analyzer.core (context_a, ast));
                if (! context_a ())
                {
                    if (cluster->routines.size () > 0)
                    {
                        auto routine (cluster->routines [0]);
                        context_a.push (routine);
                        context_a.push (context_a.parameters_begin () + 2, context_a.parameters_end ());
                        result = context_a ();
                    }
                    else
                    {
                        mu::stringstream message;
                        message << L"Cluster does not contain a routine: ";
                        message << cluster->routines.size ();
                        context_a.errors (message.str ());
                        result = false;
                    }
                }
            }
        }
        else
        {
            mu::core::type_fail (context_a.errors, typeid (mu::script::string::node), context_a.parameters (1), 1);
            result = false;
        }
	}
	else
	{
		mu::stringstream message;
		message << L"Operation ";
		message << name ();
		message << L" requires at least two arguments";
		context_a.errors (message.str ());
		result = false;
	}
	return result;*/
}

mu::string mu::script::run::operation::name ()
{
	return mu::string (U"mu::script::run::operation");
}