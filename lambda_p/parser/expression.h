#pragma once

#include <lambda_p/parser/state.h>

#include <boost/function.hpp>

#include <map>
#include <vector>

namespace lambda_p
{
	namespace core
	{
		class expression;
	}
	namespace parser
	{
		class parser;
		class routine;
		class expression : public lambda_p::parser::state
		{
		public:
			expression (lambda_p::parser::parser & parser_a, lambda_p::parser::routine & routine_a, boost::function <void (lambda_p::core::expression * expression)> target_a);
			boost::function <void (lambda_p::core::expression * expression)> target;
			lambda_p::parser::routine & routine;
			lambda_p::parser::parser & parser;
			bool has_nested_expression;
			bool is_naming;
			std::vector <lambda_p::core::expression *> expressions;
			std::map <std::wstring, size_t> local_unresolved;
			std::vector <std::wstring> local_names;
			void parse (lambda_p::tokens::token * token) override;
			void nested_expression_sink (lambda_p::core::expression * expression_a);
		};
	}
}

