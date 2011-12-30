#pragma once

#include <lambda_p_serialization/lexer/lexer.h>
#include <lambda_p_serialization/parser/parser.h>
#include <lambda_p_serialization/analyzer/analyzer.h>

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
		builder (std::map <std::wstring, boost::shared_ptr <lambda_p_serialization::parser::state_factory>> keywords_a, std::map <std::wstring, boost::shared_ptr <lambda_p_serialization::parser::reference>> & globals_a);
		void finish ();
		void operator () (std::wstring & string);
		void operator () (wchar_t const * string);
		void operator () (boost::shared_ptr <lambda_p_serialization::lexer::character_stream> source);
		void operator << (boost::shared_ptr <lambda_p_serialization::lexer::character_stream> source);
		virtual std::map <std::wstring, boost::shared_ptr <lambda_p_serialization::parser::reference>> globals ();
		virtual std::map <std::wstring, boost::shared_ptr <lambda_p_serialization::parser::state_factory>> keywords ();
		bool error ();
		void error_message (std::wostream & out);
		lambda_p_serialization::parser::parser parser;
		lambda_p_serialization::lexer::lexer lexer;
		lambda_p_serialization::analyzer::analyzer analyzer;
	};
}

