#include <mu/script/runtime/fixed.h>

#include <mu/core/check.h>
#include <mu/script/runtime/locals.h>
#include <mu/script/context.h>

mu::script::runtime::fixed::fixed (mu::core::node * node_a)
	: node (node_a)
{
}

bool mu::script::runtime::fixed::operator () (mu::script::context & context_a)
{
	bool valid (mu::core::check <mu::script::runtime::locals> (context_a));
	if (valid)
	{
		context_a.push (node);
	}
	return valid;
}