#pragma once

#include <lambda_p_serialization/tokens/visitor.h>

#include <boost/function.hpp>

#include <vector>

namespace lambda_p_serialization
{
	namespace ast
	{
		class node;
		class expression;
	}
	namespace parser
	{
		class parser;
		class full : public lambda_p_serialization::tokens::visitor
		{
		public:
			full (lambda_p_serialization::parser::parser & parser_a, boost::function <void (boost::shared_ptr <lambda_p_serialization::ast::expression>)> target_a, std::vector <boost::shared_ptr <lambda_p_serialization::ast::node>> values_a, std::vector <std::wstring> names_a);
			void operator () (lambda_p_serialization::tokens::divider * token) override;
			void operator () (lambda_p_serialization::tokens::identifier * token) override;
			void operator () (lambda_p_serialization::tokens::left_square * token) override;
			void operator () (lambda_p_serialization::tokens::right_square * token) override;
			void operator () (lambda_p_serialization::tokens::stream_end * token) override;
			void unexpected_token (lambda_p_serialization::tokens::token * token);
			lambda_p_serialization::parser::parser & parser;
			boost::function <void (boost::shared_ptr <lambda_p_serialization::ast::expression>)> target;
			std::vector <boost::shared_ptr <lambda_p_serialization::ast::node>> values;
			std::vector <std::wstring> names;
			std::wstring full_name;
		};
	}
}

