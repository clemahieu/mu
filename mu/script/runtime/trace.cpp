#include <mu/script/runtime/trace.h>

#include <mu/script/context.h>

mu::script::runtime::trace::trace (mu::script::context & context_a, boost::shared_ptr <mu::script::operation> node_a)
	: context (context_a)
{
	context_a.function_stack.push_back (node_a);
}

mu::script::runtime::trace::~trace ()
{
	context.function_stack.pop_back ();
}