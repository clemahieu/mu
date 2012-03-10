#include "operation.h"

#include <mu/core/errors/error_target.h>
#include <mu/script/string/node.h>
#include <mu/io/lexer/istream_input.h>
#include <mu/script_io/builder.h>
#include <mu/io/source.h>
#include <mu/script/runtime/routine.h>
#include <mu/script/cluster/node.h>
#include <mu/script/load/operation.h>
#include <mu/script/extensions/node.h>
#include <mu/script/analyzer/operation.h>
#include <mu/script/check.h>

#include <boost/filesystem.hpp>
#include <boost/bind.hpp>
#include <boost/make_shared.hpp>

#include <sstream>

void mu::script::run::operation::operator () (mu::script::context & context_a)
{
	if (context_a.parameters.size () > 1)
	{
		auto extensions (boost::dynamic_pointer_cast <mu::script::extensions::node> (context_a.parameters [0]));
		auto file (boost::dynamic_pointer_cast <mu::script::string::node> (context_a.parameters [1]));
		if (extensions.get () != nullptr)
		{
			if (file.get () != nullptr)
			{
				mu::script::load::operation load;
				auto ast (load.core (context_a.errors, file));
				if (! (*context_a.errors) ())
				{
					mu::script::analyzer::operation analyzer;
					auto cluster (analyzer.core (context_a.errors, extensions, ast));
					if (! (*context_a.errors) ())
					{
						if (cluster->routines.size () > 0)
						{
							auto routine (cluster->routines [0]);
							std::vector <boost::shared_ptr <mu::core::node>> arguments (context_a.parameters.begin () + 2, context_a.parameters.end ());
							auto ctx (mu::script::context (context_a.errors, arguments, context_a.results, context_a.stack));
							(*routine) (ctx);
						}
						else
						{
							std::wstringstream message;
							message << L"Cluster does not contain a routine: ";
							message << cluster->routines.size ();
							(*context_a.errors) (message.str ());
						}
					}
				}
			}
			else
			{
				mu::script::invalid_type (context_a.errors, typeid (*context_a.parameters [1].get ()), typeid (mu::script::string::node), 1);
			}
		}
		else
		{
			invalid_type (context_a.errors, typeid (*context_a.parameters [0].get ()), typeid (mu::script::extensions::node), 0);
		}
	}
	else
	{
		std::wstringstream message;
		message << L"Operation ";
		message << name ();
		message << L" requires at least two arguments";
		(*context_a.errors) (message.str ());
	}
}

std::wstring mu::script::run::operation::name ()
{
	return std::wstring (L"mu::script::run::operation");
}