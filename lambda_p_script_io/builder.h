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
	namespace closure
	{
		class single;
	}
	namespace cluster
	{
		class node;
	}
	namespace exec
	{
		class operation;
	}
}
namespace lambda_p_script_io
{
	boost::shared_ptr <lambda_p_io::analyzer::extensions::extensions> extensions ();
	class builder
	{
	public:
		builder ();
		builder (boost::shared_ptr <lambda_p_io::analyzer::extensions::extensions> extensions_a);
		boost::shared_ptr <lambda_p::errors::error_list> errors;
		lambda_p_script_io::synthesizer synthesizer;
		lambda_p_io::analyzer::analyzer analyzer;
		lambda_p_io::parser::parser parser;
		lambda_p_io::lexer::lexer lexer;
		void set_self ();
		boost::shared_ptr <lambda_p_script::closure::single> self;
		void operator () (boost::shared_ptr <lambda_p::cluster> cluster_a);
		std::vector <boost::shared_ptr <lambda_p_script::cluster::node>> clusters;
	};
}

