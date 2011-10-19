#include "routine_builder.h"

#include <sstream>

#include <boost/bind.hpp>

lambda_p::routine_builder::routine_builder ()
	: parser (boost::bind (&(lambda_p::parser::routine_vector::operator()), &routines, _1)),
	lexer (boost::bind (&(lambda_p::parser::parser::operator()), &parser, _1))
{
}

void lambda_p::routine_builder::operator << (std::wistream & source)
{
	while (!source.eof ())
	{
		lexer (source.get ());
	}
}

void lambda_p::routine_builder::operator () (std::wstring & string)
{
	std::wstringstream stream (string);
	operator << (stream);
}

void lambda_p::routine_builder::operator () (wchar_t const * string)
{
	std::wstring str (string);
	operator () (str);
}