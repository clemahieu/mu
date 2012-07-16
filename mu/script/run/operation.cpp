#include <mu/script/run/operation.h>

#include <mu/core/errors/error_target.h>
#include <mu/script/string/node.h>
#include <mu/io/lexer/istream_input.h>
#include <mu/io/source.h>
#include <mu/script/load/operation.h>
#include <mu/script/extensions/node.h>
#include <mu/script/analyzer/operation.h>
#include <mu/script/check.h>
#include <mu/core/cluster.h>
#include <mu/core/routine.h>

#include <boost/filesystem.hpp>
#include <boost/bind.hpp>

#include <sstream>

bool mu::script::run::operation::operator () (mu::script::context & context_a)
{
	bool result (true);
	if (context_a.parameters_size () > 1)
	{
		auto extensions (dynamic_cast <mu::script::extensions::node *> (context_a.parameters (0)));
		auto file (dynamic_cast <mu::script::string::node *> (context_a.parameters (1)));
		if (extensions != nullptr)
		{
			if (file != nullptr)
			{
				mu::script::load::operation load;
				auto ast (load.core (context_a, file));
				if (! context_a ())
				{
					mu::script::analyzer::operation analyzer;
					auto cluster (analyzer.core (context_a, extensions, ast));
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
				mu::script::invalid_type (context_a, context_a.parameters (1), typeid (mu::script::string::node), 1);
				result = false;
			}
		}
		else
		{
			invalid_type (context_a, context_a.parameters (0), typeid (mu::script::extensions::node), 0);
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
	return result;
}

mu::string mu::script::run::operation::name ()
{
	return mu::string (U"mu::script::run::operation");
}