#pragma once

#include <lambda_p_io/lexer/lexer.h>
#include <lambda_p_io/parser/parser.h>
#include <lambda_p_io/analyzer/analyzer.h>
#include <lambda_p/container.h>
#include <lambda_p_io/source.h>

#include <vector>

namespace lambda_p
{
	namespace core
	{
		class routine;
	}
	namespace errors
	{
		class error_list;
	}
}
namespace lambda_p_io
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
		void operator () (boost::shared_ptr <lambda_p_io::lexer::character_stream> source);
		void operator << (boost::shared_ptr <lambda_p_io::lexer::character_stream> source);
		bool error ();
		void error_message (std::wostream & out);
		void analyzer_output (boost::shared_ptr <lambda_p::core::routine> routine_a);
		void parser_output (boost::shared_ptr <lambda_p_io::ast::expression> expression_a);
		void lexer_output (lambda_p_io::tokens::token * token_a);
		std::vector <boost::shared_ptr <lambda_p::core::routine>> routines;
		boost::shared_ptr <lambda_p::errors::error_list> errors;
		lambda_p_io::analyzer::analyzer analyzer;
		lambda_p_io::parser::parser parser;
		lambda_p_io::lexer::lexer lexer;
		lambda_p_io::source source;
	};
}

