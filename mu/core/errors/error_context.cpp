#include <mu/core/errors/error_context.h>

mu::core::errors::error_context::error_context (mu::core::errors::error_target * target_a, mu::io::debugging::context context_a)
	: target (target_a),
	context (context_a)
{
}

void mu::core::errors::error_context::operator () (mu::core::errors::error * error)
{
	(*target) (error);
}

bool mu::core::errors::error_context::operator () ()
{
	return (*target) ();
}

void mu::core::errors::error_context::print (mu::ostream & target_a)
{
    target->print (target_a);
}