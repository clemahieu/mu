#include <mu/script/debugging/trace_target.h>

mu::script::debugging::trace_target::trace_target (boost::shared_ptr <mu::core::errors::error_target> target_a, mu::script::context & context_a)
	: target (target_a),
	context (context_a)
{
}

void mu::script::debugging::trace_target::operator () (boost::shared_ptr <mu::core::errors::error> error)
{

}

bool mu::script::debugging::trace_target::operator () ()
{
	auto result ((*target) ());
	return result;
}

void mu::script::debugging::trace_target::print (std::wostream & target_a)
{
	target->print (target_a);
}