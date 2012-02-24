#pragma once

#include <core/context.h>
#include <lambda_p_io/tokens/visitor.h>

#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>

#include <vector>

namespace lambda_p_io
{
	namespace ast
	{
		class node;
		class expression;
		class identifier;
	}
	namespace parser
	{
		class parser;
		class full : public lambda_p_io::tokens::visitor
		{
		public:
			full (lambda_p_io::parser::parser & parser_a, boost::function <void (boost::shared_ptr <lambda_p_io::ast::expression>)> target_a, std::vector <boost::shared_ptr <lambda_p_io::ast::node>> values_a, std::vector <boost::shared_ptr <lambda_p_io::ast::identifier>> names_a, mu::core::context first_a);
			void operator () (lambda_p_io::tokens::divider * token) override;
			void operator () (lambda_p_io::tokens::identifier * token) override;
			void operator () (lambda_p_io::tokens::left_square * token) override;
			void operator () (lambda_p_io::tokens::right_square * token) override;
			void operator () (lambda_p_io::tokens::stream_end * token) override;
			void operator () (lambda_p_io::tokens::parameters * token) override;
			void unexpected_token (lambda_p_io::tokens::token * token, mu::core::context context_a);
			lambda_p_io::parser::parser & parser;
			boost::function <void (boost::shared_ptr <lambda_p_io::ast::expression>)> target;
			std::vector <boost::shared_ptr <lambda_p_io::ast::node>> values;
			std::vector <boost::shared_ptr <lambda_p_io::ast::identifier>> names;
			boost::shared_ptr <lambda_p_io::ast::identifier> full_name;			
			mu::core::context first;
		};
	}
}

