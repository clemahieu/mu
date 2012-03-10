#include <mu/script/runtime/trace_registration.h>

#include <mu/script/runtime/frame.h>

mu::script::runtime::trace_registration::trace_registration (std::vector <std::type_info const *> & stack_a, std::type_info const * info_a)
	: stack (stack_a)
{
	stack.push_back (info_a);
}

mu::script::runtime::trace_registration::~trace_registration ()
{
	stack.pop_back ();
}