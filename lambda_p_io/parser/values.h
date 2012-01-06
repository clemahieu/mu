#pragma once

#include <lambda_p_io/tokens/visitor.h>

#include <boost/function.hpp>

#include <vector>

namespace lambda_p_io
{
	namespace ast
	{
		class node;
		class expression;
	}
	namespace parser
	{
		class parser;
		class values : public lambda_p_io::tokens::visitor
		{
		public:
			values (lambda_p_io::parser::parser & parser_a, boost::function <void (boost::shared_ptr <lambda_p_io::ast::expression>)> target_a);
			void operator () (lambda_p_io::tokens::divider * token) override;
			void operator () (lambda_p_io::tokens::identifier * token) override;
			void operator () (lambda_p_io::tokens::left_square * token) override;
			void operator () (lambda_p_io::tokens::right_square * token) override;
			void operator () (lambda_p_io::tokens::stream_end * token) override;
			void operator () (lambda_p_io::tokens::parameters * token) override;
			void subexpression (boost::shared_ptr <lambda_p_io::ast::expression> expression);
			std::vector <boost::shared_ptr <lambda_p_io::ast::node>> values_m;
			lambda_p_io::parser::parser & parser;
			boost::function <void (boost::shared_ptr <lambda_p_io::ast::expression>)> target;
		};
	}
}

