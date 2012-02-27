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

mu::script::exec::operation::operation (boost::shared_ptr <mu::io::analyzer::extensions::extensions> extensions_a)
	: extensions (extensions_a)
{
}

void mu::script::exec::operation::perform (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results)
{
	if (parameters.size () > 0)
	{
		std::vector <boost::shared_ptr <mu::core::node>> a1;
		std::vector <boost::shared_ptr <mu::core::node>> r1;
		auto extensions_l (boost::make_shared <mu::script::extensions::node> ());
		extensions_l->extensions = extensions;
		a1.push_back (extensions_l);
		a1.push_back (parameters [0]);
		mu::script::load::operation load;
		load.perform (errors_a, a1, r1);
		if (! (*errors_a) ())
		{
			auto cluster (boost::static_pointer_cast <mu::script::cluster::node> (r1 [0]));
			if (cluster->routines.size () > 0)
			{
				auto routine (cluster->routines [0]);
				std::vector <boost::shared_ptr <mu::core::node>> arguments (parameters.begin () + 1, parameters.end ());
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
		std::wstringstream message;
		message << L"Operation ";
		message << name ();
		message << L" requires at least one argument";
		(*errors_a) (message.str ());
	}
}

std::wstring mu::script::exec::operation::name ()
{
	return std::wstring (L"mu::script::exec::operation");
}