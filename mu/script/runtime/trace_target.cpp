#include <mu/script/runtime/trace_target.h>		

#include <mu/script/runtime/stacktrace_error.h>
#include <mu/script/context.h>
#include <mu/script/debugging/mapping.h>

#include <boost/make_shared.hpp>

mu::script::runtime::trace_target::trace_target (mu::script::context & context_a, mu::script::debugging::mapping & mapping_a, boost::shared_ptr <mu::core::errors::error_target> target_a)
	: context (context_a),
	target (target_a),
	mapping (mapping_a)
{
}

void mu::script::runtime::trace_target::operator () (boost::shared_ptr <mu::core::errors::error> error, mu::core::context context_a)
{
	(*target) (boost::make_shared <mu::script::runtime::stacktrace_error> (context, mapping, error), context_a);
}

bool mu::script::runtime::trace_target::operator () ()
{
	auto result ((*target) ());
	return result;
}

void mu::script::runtime::trace_target::print (std::wostream & target_a)
{
	target->print (target_a);
}