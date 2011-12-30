#pragma once

#include <lambda_p_serialization/tokens/visitor.h>

#include <vector>

#include <boost/shared_ptr.hpp>
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
		enum expression_state
		{
			values,
			individual_names,
			full_name
		};
		class expression : public lambda_p_serialization::tokens::visitor
		{
		public:
			expression (lambda_p_serialization::parser::parser & parser_a, boost::function <void (boost::shared_ptr <lambda_p_serialization::ast::node>)> target_a);
			void parse (lambda_p_serialization::tokens::token * token) override;
			void parse_value (lambda_p_serialization::tokens::token * token);
			void parse_individual_names (lambda_p_serialization::tokens::token * token);
			void parse_full_name (lambda_p_serialization::tokens::token * token);
			void subvalue (boost::shared_ptr <lambda_p_serialization::ast::node> value);
			lambda_p_serialization::parser::parser & parser;
			boost::function <void (boost::shared_ptr <lambda_p_serialization::ast::node>)> target;
			std::vector <boost::shared_ptr <lambda_p_serialization::ast::node>> values;
			std::vector <std::wstring> individual_names;
			std::wstring full_name;
			lambda_p_serialization::parser::expression_state state;
		};
	}
}

