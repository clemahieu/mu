#pragma once

#include <lambda_p_io/tokens/visitor.h>

#include <boost/function.hpp>

namespace lambda_p
{
	namespace core
	{
		class routine;
	}
}
namespace lambda_p_io
{	
	namespace ast
	{
		class expression;
	}
	namespace parser
	{
		class parser;
		class begin : public lambda_p_io::tokens::visitor
		{
		public:
			begin (lambda_p_io::parser::parser & parser_a, boost::function <void (boost::shared_ptr <lambda_p_io::ast::expression>)> target_a);
			void operator () (lambda_p_io::tokens::divider * token) override;
			void operator () (lambda_p_io::tokens::identifier * token) override;
			void operator () (lambda_p_io::tokens::left_square * token) override;
			void operator () (lambda_p_io::tokens::right_square * token) override;
			void operator () (lambda_p_io::tokens::stream_end * token) override;
			void unexpected_token (lambda_p_io::tokens::token * token);
			lambda_p_io::parser::parser & parser;
			boost::function <void (boost::shared_ptr <lambda_p_io::ast::expression>)> target;
		};
	}
}

