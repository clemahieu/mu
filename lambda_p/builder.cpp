#include "builder.h"

#include <sstream>

#include <boost/bind.hpp>

lambda_p::builder::builder ()
	: parser (boost::bind (&(lambda_p::parser::routine_vector::operator()), &routines, _1), injected_declarations (), injected_references ()),
	lexer (boost::bind (&(lambda_p::parser::parser::operator()), &parser, _1))
{
}

void lambda_p::builder::operator << (std::wistream & source)
{
	while (!source.eof ())
	{
		lexer (source.get ());
	}
}

void lambda_p::builder::operator () (std::wstring & string)
{
	std::wstringstream stream (string);
	operator << (stream);
}

void lambda_p::builder::operator () (wchar_t const * string)
{
	std::wstring str (string);
	operator () (str);
}

std::vector <std::pair <std::wstring, boost::shared_ptr <lambda_p::binder::node>>> lambda_p::builder::injected_declarations ()
{
	std::vector <std::pair <std::wstring, boost::shared_ptr <lambda_p::binder::node>>> result;
	return result;
}

std::vector <std::wstring> lambda_p::builder::injected_references ()
{
	std::vector <std::wstring> result;
	return result;
}