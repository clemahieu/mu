#include <mu/core/errors/error_target.h>

#include <mu/core/errors/string_error.h>

#include <gc_cpp.h>

mu::core::errors::error_target::~error_target ()
{
}

void mu::core::errors::error_target::operator () (mu::string error)
{
	(*this) (new (GC) mu::core::errors::string_error (error));
}

void mu::core::errors::error_target::operator () (char32_t const * error)
{
	(*this) (mu::string (error));
}

void mu::core::errors::error_target::print (std::wostream & target)
{
    mu::stringstream stream;
    print (stream);
    std::wstring str (stream.str ().begin (), stream.str ().end ());
    target << str;
}