#include <mu/core/errors/errors.h>

mu::core::errors::errors::errors (mu::core::errors::error_target & target_a)
	: target (target_a)
{
}

void mu::core::errors::errors::operator () (mu::core::errors::error * error)
{
	target (error);
}

bool mu::core::errors::errors::operator () ()
{
	bool result (target ());
	return result;
}

void mu::core::errors::errors::print (mu::ostream & target_a)
{
	target.print (target_a);
}

void mu::core::errors::errors::operator () (mu::string error)
{
	target (error);
}

void mu::core::errors::errors::operator () (char32_t const * error)
{
	target (error);
}