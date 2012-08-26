#include <mu/llvm_/cluster/index.h>

#include <mu/core/errors/error_list.h>
#include <mu/llvm_/cluster/node.h>
#include <mu/script/integer_node.h>
#include <mu/llvm_/function/node.h>
#include <mu/core/check.h>
#include <mu/script/context.h>

#include <sstream>

bool mu::llvm_::cluster::index::operator () (mu::script::context & context_a)
{
	bool result (mu::core::check <mu::llvm_::cluster::node, mu::script::integer::node> (context_a));
	if (result)
	{
		auto one (static_cast <mu::llvm_::cluster::node *> (context_a.parameters (0)));
		auto two (static_cast <mu::script::integer::node *> (context_a.parameters (1)));
		if (one->routines.size () > two->value)
		{
			context_a.push (one->routines [two->value]);
		}
		else
		{
			mu::stringstream message;
			message << L"Cluster only has: ";
			message << one->routines.size ();
			message << L" routines: ";
			message << two->value;
			context_a.errors (message.str ());
			result = false;
		}
	}
	return result;
}