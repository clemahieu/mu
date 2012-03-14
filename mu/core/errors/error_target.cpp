#include <mu/core/errors/error_target.h>

#include <mu/core/errors/string_error.h>

mu::core::errors::error_target::~error_target ()
{
}

void mu::core::errors::error_target::operator () (std::wstring error)
{
	(*this) (boost::shared_ptr <mu::core::errors::string_error> (new mu::core::errors::string_error (error)));
}

void mu::core::errors::error_target::operator () (wchar_t const * error)
{
	(*this) (std::wstring (error));
}