#include <mu/core/errors/null.h>

mu::core::errors::null::null ()
	: had_error (false)
{
}

void mu::core::errors::null::operator () (boost::shared_ptr <mu::core::errors::error> error)
{
	had_error = true;
}

bool mu::core::errors::null::operator () ()
{
	return had_error;
}

void mu::core::errors::null::print (std::wostream & target)
{
	had_error = true;
}

void mu::core::errors::null::operator () (std::wstring error)
{
	had_error = true;
}

void mu::core::errors::null::operator () (wchar_t const * error)
{
	had_error = true;
}