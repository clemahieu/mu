#pragma once

#include <lambda_p_serialization/tokens/visitor.h>

#include <boost/function.hpp>

namespace lambda_p
{
	namespace core
	{
		class routine;
	}
}
namespace lambda_p_serialization
{	
	namespace ast
	{
		class expression;
	}
	namespace parser
	{
		class parser;
		class begin : public lambda_p_serialization::tokens::visitor
		{
		public:
			begin (lambda_p_serialization::parser::parser & parser_a, boost::function <void (boost::shared_ptr <lambda_p_serialization::ast::expression>)> target_a);
			void operator () (lambda_p_serialization::tokens::divider * token) override;
			void operator () (lambda_p_serialization::tokens::identifier * token) override;
			void operator () (lambda_p_serialization::tokens::left_square * token) override;
			void operator () (lambda_p_serialization::tokens::right_square * token) override;
			void operator () (lambda_p_serialization::tokens::stream_end * token) override;
			void unexpected_token (lambda_p_serialization::tokens::token * token);
			lambda_p_serialization::parser::parser & parser;
			boost::function <void (boost::shared_ptr <lambda_p_serialization::ast::expression>)> target;
		};
	}
}

