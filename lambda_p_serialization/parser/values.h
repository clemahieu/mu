#pragma once

#include <lambda_p_serialization/tokens/visitor.h>

#include <boost/function.hpp>

namespace lambda_p_serialization
{
	namespace ast
	{
		class node;
	}
	namespace parser
	{
		class parser;
		class values : public lambda_p_serialization::tokens::visitor
		{
		public:
			values (lambda_p_serialization::parser::parser & parser_a, boost::function <void (boost::shared_ptr <lambda_p_serialization::ast::node>)> target_a);
			void operator () (lambda_p_serialization::tokens::divider * token) override;
			void operator () (lambda_p_serialization::tokens::identifier * token) override;
			void operator () (lambda_p_serialization::tokens::left_square * token) override;
			void operator () (lambda_p_serialization::tokens::right_square * token) override;
			void operator () (lambda_p_serialization::tokens::stream_end * token) override;
			std::vector <boost::shared_ptr <lambda_p_serialization::ast::node>> values_m;
			lambda_p_serialization::parser::parser & parser;
			boost::function <void (boost::shared_ptr <lambda_p_serialization::ast::node>)> target;
		};
	}
}

