#include "get_named.h"

#include <mu/core/errors/error_target.h>
#include <mu/script/cluster/node.h>
#include <mu/script/string/node.h>
#include <mu/script/runtime/routine.h>

#include <sstream>

void mu::script::cluster::get_named::operator () (mu::script::context & context_a)
{
	auto one (boost::dynamic_pointer_cast <mu::script::cluster::node> (context_a.parameters [0]));
	auto two (boost::dynamic_pointer_cast <mu::script::string::node> (context_a.parameters [1]));
	if (one.get () != nullptr)
	{
		if (two.get () != nullptr)
		{
			auto existing (one->names.find (two->string));
			if (existing != one->names.end ())
			{
				context_a.results.push_back (existing->second);
			}
			else
			{
				std::wstringstream message;
				message << L"Unable to get routine named: ";
				message << two->string;
				(*context_a.errors) (message.str ());
			}
		}
		else
		{
			invalid_type (context_a.errors, context_a.parameters [1], 1);
		}
	}
	else
	{
		invalid_type (context_a.errors, context_a.parameters [0], 0);
	}
}
	
size_t mu::script::cluster::get_named::count ()
{
	return 2;
}