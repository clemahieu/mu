#pragma once

#include <lambda_p/parser/routine_vector.h>
#include <lambda_p/lexer/simple_lexer.h>
#include <lambda_p/parser/simple_parser.h>

namespace lambda_p
{
	class routine_builder
	{
	public:
		routine_builder ();
		void operator () (::std::wstring & string);
		void operator () (wchar_t const * string);
		void operator << (::std::wistream & source);
		::lambda_p::parser::routine_vector routines;
		::lambda_p::parser::simple_parser parser;
		::lambda_p::lexer::simple_lexer lexer;
	};
}

