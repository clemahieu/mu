#include <mu/script/runtime/context_trace.h>

#include <mu/script/context.h>

mu::script::runtime::context_trace::context_trace (mu::script::context & context_a, mu::core::context ctx_a)
	: context (context_a)
{
	context.context_stack.push_back (ctx_a);
}

mu::script::runtime::context_trace::~context_trace ()
{
	context.context_stack.pop_back ();
}