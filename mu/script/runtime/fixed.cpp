#include <mu/script/runtime/fixed.h>

#include <mu/script/check.h>
#include <mu/script/runtime/locals.h>

mu::script::runtime::fixed::fixed (boost::shared_ptr <mu::core::node> node_a)
	: node (node_a)
{
}

bool mu::script::runtime::fixed::operator () (mu::script::context & context_a)
{
	bool valid (mu::script::check <mu::script::runtime::locals> () (context_a));
	if (valid)
	{
		context_a.push (node);
	}
	return valid;
}