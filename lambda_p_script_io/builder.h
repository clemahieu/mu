#pragma once

#include <lambda_p_io/source.h>
#include <lambda_p_io/lexer/lexer.h>
#include <lambda_p_io/parser/parser.h>
#include <lambda_p_io/analyzer/analyzer.h>
#include <lambda_p/errors/error_list.h>
#include <lambda_p_script_io/synthesizer.h>

#include <vector>

namespace lambda_p_script
{
	namespace exec
	{
		class operation;
	}
}
namespace lambda_p_script_io
{
	class builder
	{
	public:
		builder ();
		builder (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>> extensions_a);
		boost::shared_ptr <lambda_p_script::exec::operation> exec;
		std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>> extensions ();
		boost::shared_ptr <lambda_p::errors::error_list> errors;
		lambda_p_script_io::synthesizer synthesizer;
		lambda_p_io::analyzer::analyzer analyzer;
		lambda_p_io::parser::parser parser;
		lambda_p_io::lexer::lexer lexer;
		void operator () (boost::shared_ptr <lambda_p_script::routine> routine_a);
		std::vector <boost::shared_ptr <lambda_p_script::routine>> routines;
	};
}

