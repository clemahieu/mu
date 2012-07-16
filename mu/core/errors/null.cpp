#include <mu/core/errors/null.h>

mu::core::errors::null::null ()
	: had_error (false)
{
}

void mu::core::errors::null::operator () (mu::core::errors::error * error)
{
	had_error = true;
}

bool mu::core::errors::null::operator () ()
{
	return had_error;
}

void mu::core::errors::null::print (mu::ostream & target)
{
	had_error = true;
}

void mu::core::errors::null::operator () (mu::string error)
{
	had_error = true;
}

void mu::core::errors::null::operator () (char32_t const * error)
{
	had_error = true;
}