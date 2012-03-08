#include "index.h"

#include <mu/core/errors/error_list.h>
#include <mu/llvm_/cluster/node.h>
#include <mu/script/integer/node.h>
#include <mu/llvm_/function/node.h>

#include <sstream>

void mu::llvm_::cluster::index::operator () (mu::script::context & context_a)
{
	auto one (boost::dynamic_pointer_cast <mu::llvm_::cluster::node> (context_a.parameters [0]));
	auto two (boost::dynamic_pointer_cast <mu::script::integer::node> (context_a.parameters [1]));
	if (one.get () != nullptr)
	{
		if (two.get () != nullptr)
		{
			if (one->routines.size () > two->value)
			{
				context_a.results.push_back (one->routines [two->value]);
			}
			else
			{
				std::wstringstream message;
				message << L"Cluster only has: ";
				message << one->routines.size ();
				message << L" routines: ";
				message << two->value;
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

size_t mu::llvm_::cluster::index::count ()
{
	return 2;
}