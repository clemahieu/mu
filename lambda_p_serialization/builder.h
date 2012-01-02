#pragma once

#include <lambda_p_serialization/lexer/lexer.h>
#include <lambda_p_serialization/parser/parser.h>
#include <lambda_p_serialization/analyzer/analyzer.h>
#include <lambda_p/container.h>
#include <lambda_p_serialization/source.h>

#include <vector>

namespace lambda_p
{
	namespace core
	{
		class routine;
	}
}
namespace lambda_p_serialization
{
	namespace lexer
	{
		class character_stream;
	}
	class builder
	{
	public:
		builder ();
		void finish ();
		void operator () (std::wstring & string);
		void operator () (wchar_t const * string);
		void operator () (boost::shared_ptr <lambda_p_serialization::lexer::character_stream> source);
		void operator << (boost::shared_ptr <lambda_p_serialization::lexer::character_stream> source);
		bool error ();
		void error_message (std::wostream & out);
		void new_error (std::wstring message);
		void analyzer_output (boost::shared_ptr <lambda_p::core::routine> routine_a);
		void parser_output (boost::shared_ptr <lambda_p_serialization::ast::expression> expression_a);
		void lexer_output (lambda_p_serialization::tokens::token * token_a);
		std::vector <boost::shared_ptr <lambda_p::core::routine>> routines;
		lambda_p_serialization::analyzer::analyzer analyzer;
		lambda_p_serialization::parser::parser parser;
		lambda_p_serialization::lexer::lexer lexer;
		lambda_p_serialization::source source;
	};
}

