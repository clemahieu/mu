#pragma once

#include <lambda_p_io/source.h>
#include <lambda_p_io/lexer/lexer.h>
#include <lambda_p_io/parser/parser.h>
#include <lambda_p_io/analyzer/analyzer.h>
#include <lambda_p_io/ast/visitor.h>

#include <vector>

namespace mu
{
	namespace core
	{
		namespace errors
		{
			class error_list;
		}
	}
}
namespace lambda_p_io
{
	namespace ast
	{
		class node;
		class cluster;
	}
	class builder : public lambda_p_io::ast::visitor
	{
	public:
		builder ();
		boost::shared_ptr <mu::core::errors::error_list> errors;
		lambda_p_io::parser::parser parser;
		lambda_p_io::lexer::lexer lexer;
		void add (boost::shared_ptr <lambda_p_io::ast::node> node_a);
		void operator () (lambda_p_io::ast::parameters * parameters_a) override;
		void operator () (lambda_p_io::ast::expression * expression_a) override;
		void operator () (lambda_p_io::ast::identifier * identifier_a) override;
		void operator () (lambda_p_io::ast::end * end_a) override;
		boost::shared_ptr <lambda_p_io::ast::node> current;
		boost::shared_ptr <lambda_p_io::ast::cluster> building;
		std::vector <boost::shared_ptr <lambda_p_io::ast::cluster>> clusters;
	};
}

