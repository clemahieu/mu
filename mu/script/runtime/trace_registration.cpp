#include <mu/script/runtime/trace_registration.h>

#include <mu/script/runtime/frame.h>

mu::script::runtime::trace_registration::trace_registration (mu::script::runtime::frame & frame_a, std::type_info const * info_a)
	: frame (frame_a)
{
	//context.trace.push (info_a);
}

mu::script::runtime::trace_registration::~trace_registration ()
{
	//context.trace.pop ();
}