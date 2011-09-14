#pragma once

#include <lambda_p/parser/routine_vector.h>
#include <lambda_p/parser/simple_parser.h>
#include <lambda_p/lexer/simple_lexer.h>

#include <string>

namespace lambda_p_repl
{
	class routine_input
	{
	public:
		routine_input (void);
		~routine_input (void);
		void operator () (::std::wistream & input_stream, ::std::wostream & output_stream);
		void operator () (wchar_t character);
		void operator () (::std::wstring & string);
		bool error ();
		void error_message (::std::wstring & message);
		void token_sink (::lambda_p::tokens::token *);
		::lambda_p::parser::routine_vector routines;
		::lambda_p::parser::simple_parser parser;
		::lambda_p::lexer::simple_lexer lexer;
	};
}

