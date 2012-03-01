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

#include <boost/filesystem.hpp>
#include <boost/bind.hpp>
#include <boost/make_shared.hpp>

#include <sstream>

void mu::script::run::operation::perform (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results)
{
	if (parameters.size () > 1)
	{
		auto extensions (boost::dynamic_pointer_cast <mu::script::extensions::node> (parameters [0]));
		auto file (boost::dynamic_pointer_cast <mu::script::string::node> (parameters [1]));
		if (extensions.get () != nullptr)
		{
			if (file.get () != nullptr)
			{
				mu::script::load::operation load;
				auto cluster (load.core (errors_a, extensions, file));
				if (! (*errors_a) ())
				{
					if (cluster->routines.size () > 0)
					{
						auto routine (cluster->routines [0]);
						std::vector <boost::shared_ptr <mu::core::node>> arguments (parameters.begin () + 2, parameters.end ());
						routine->perform (errors_a, arguments, results);
					}
					else
					{
						std::wstringstream message;
						message << L"Cluster does not contain a routine: ";
						message << cluster->routines.size ();
						(*errors_a) (message.str ());
					}
				}
			}
			else
			{
				invalid_type (errors_a, parameters [1], 1);
			}
		}
		else
		{
			invalid_type (errors_a, parameters [0], 0);
		}
	}
	else
	{
		std::wstringstream message;
		message << L"Operation ";
		message << name ();
		message << L" requires at least two arguments";
		(*errors_a) (message.str ());
	}
}

std::wstring mu::script::run::operation::name ()
{
	return std::wstring (L"mu::script::run::operation");
}