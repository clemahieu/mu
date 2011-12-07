#pragma once

#include <lambda_p/parser/state.h>
#include <lambda_p/parser/expression_sink.h>
#include <lambda_p/parser/expression_state.h>

#include <boost/function.hpp>

#include <map>
#include <vector>

namespace lambda_p
{
	namespace core
	{
		class expression_list;
	}
	namespace parser
	{
		class parser;
		class routine;
		class expression : public lambda_p::parser::state, public lambda_p::parser::expression_sink
		{
		public:
			expression (lambda_p::parser::parser & parser_a, lambda_p::parser::routine & routine_a, lambda_p::core::expression_list * list_a);
			void sink (lambda_p::core::expression * expression) override;
			lambda_p::core::expression_list * list;
			lambda_p::parser::routine & routine;
			lambda_p::parser::parser & parser;
			lambda_p::parser::expression_state::expression_state state;
			std::vector <std::wstring> local_names;
			std::wstring full_name;
			void resolve ();
			void back_resolve (std::wstring identifier, lambda_p::core::expression * expression);
			void parse (lambda_p::tokens::token * token) override;
		};
	}
}

