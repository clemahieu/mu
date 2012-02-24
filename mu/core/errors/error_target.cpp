#include "error_target.h"

#include <mu/core/errors/string_error.h>

void mu::core::errors::error_target::operator () (std::wstring error)
{
	(*this) (error, mu::core::context ());
}

void mu::core::errors::error_target::operator () (wchar_t const * error)
{
	(*this) (error, mu::core::context ());
}

void mu::core::errors::error_target::operator () (std::wstring error, mu::core::context context_a)
{
	(*this) (boost::shared_ptr <mu::core::errors::string_error> (new mu::core::errors::string_error (error)), context_a);
}

void mu::core::errors::error_target::operator () (wchar_t const * error, mu::core::context context_a)
{
	(*this) (std::wstring (error), context_a);
}