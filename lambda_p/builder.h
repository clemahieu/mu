#pragma once

#include <lambda_p/parser/routine_vector.h>
#include <lambda_p/lexer/lexer.h>
#include <lambda_p/parser/parser.h>

namespace lambda_p
{
	class builder
	{
	public:
		builder ();
		void operator () (std::wstring & string);
		void operator () (wchar_t const * string);
		void operator << (std::wistream & source);
		virtual std::vector <std::pair <std::wstring, boost::shared_ptr <lambda_p::binder::node>>> injected_declarations ();
		virtual std::vector <std::wstring> injected_references ();
		lambda_p::parser::routine_vector routines;
		lambda_p::parser::parser parser;
		lambda_p::lexer::lexer lexer;
	};
}

