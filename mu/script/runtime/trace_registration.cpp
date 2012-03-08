#include <mu/script/runtime/trace_registration.h>

#include <mu/script/runtime/context.h>

mu::script::runtime::trace_registration::trace_registration (mu::script::runtime::context & context_a, std::type_info const * info_a)
	: context (context_a)
{
	//context.trace.push (info_a);
}

mu::script::runtime::trace_registration::~trace_registration ()
{
	//context.trace.pop ();
}