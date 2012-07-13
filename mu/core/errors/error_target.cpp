#include <mu/core/errors/error_target.h>

#include <mu/core/errors/string_error.h>

#include <gc_cpp.h>

mu::core::errors::error_target::~error_target ()
{
}

void mu::core::errors::error_target::operator () (std::wstring error)
{
	(*this) (new (GC) mu::core::errors::string_error (error));
}

void mu::core::errors::error_target::operator () (wchar_t const * error)
{
	(*this) (std::wstring (error));
}