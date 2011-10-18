#pragma once

#include <lambda_p/parser/routine_vector.h>
#include <lambda_p/parser/parser.h>
#include <lambda_p/lexer/lexer.h>

#include <string>

namespace lambda_p_repl
{
	class character_stream;
	class routine_input
	{
	public:
		routine_input (void);
		~routine_input (void);
		void operator () (::boost::shared_ptr < ::lambda_p_repl::character_stream> input_stream);
		void operator () (wchar_t character);
		void operator () (::std::wstring & string);
		bool error ();
		void error_message (::std::wstring & message);
		::lambda_p::parser::routine_vector routines;
		::lambda_p::parser::parser parser;
		::lambda_p::lexer::lexer lexer;
	};
}

