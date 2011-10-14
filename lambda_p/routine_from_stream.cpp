#include "routine_from_stream.h"

#include <sstream>

#include <boost/bind.hpp>

lambda_p::routine_from_stream::routine_from_stream ()
	: parser (::boost::bind (&(::lambda_p::parser::routine_vector::operator()), &routines, _1)),
	lexer (::boost::bind (&(::lambda_p::parser::simple_parser::operator()), &parser, _1))
{
}

void lambda_p::routine_from_stream::operator << (::std::wistream & source)
{
	while (!source.eof ())
	{
		lexer (source.get ());
	}
}

void lambda_p::routine_from_stream::operator () (::std::wstring & string)
{
	::std::wstringstream stream (string);
	operator << (stream);
}

void lambda_p::routine_from_stream::operator () (wchar_t const * string)
{
	::std::wstring str (string);
	operator () (str);
}