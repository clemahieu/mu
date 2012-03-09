#include "index.h"

#include <mu/core/errors/error_list.h>
#include <mu/llvm_/cluster/node.h>
#include <mu/script/integer/node.h>
#include <mu/llvm_/function/node.h>
#include <mu/script/check.h>

#include <sstream>

void mu::llvm_::cluster::index::operator () (mu::script::context & context_a)
{
	if (mu::script::check <mu::llvm_::cluster::node, mu::script::integer::node> () (context_a))
	{
		auto one (boost::static_pointer_cast <mu::llvm_::cluster::node> (context_a.parameters [0]));
		auto two (boost::static_pointer_cast <mu::script::integer::node> (context_a.parameters [1]));
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
}

size_t mu::llvm_::cluster::index::count ()
{
	return 2;
}