#pragma once

#include <lambda_p/parser/state.h>
#include <lambda_p/parser/expression_sink.h>
#include <lambda_p/parser/expression_state.h>

#include <boost/shared_ptr.hpp>

#include <map>
#include <vector>

namespace lambda_p_serialization
{
	namespace core
	{
		class list;
	}
	namespace parser
	{
		class parser;
		class routine;
		class expression : public lambda_p::parser::state, public lambda_p::parser::expression_sink
		{
		public:
			expression (lambda_p::parser::parser & parser_a, lambda_p::parser::routine & routine_a, boost::shared_ptr <lambda_p::core::list> list_a);
			void sink (boost::shared_ptr <lambda_p::core::expression> expression) override;
			boost::shared_ptr <lambda_p::core::list> list;
			lambda_p::parser::routine & routine;
			lambda_p::parser::parser & parser;
			lambda_p::parser::expression_state::expression_state state;
			std::vector <std::wstring> local_names;
			std::wstring full_name;
			void resolve ();
			void back_resolve (std::wstring identifier, boost::shared_ptr <lambda_p::core::expression> expression);
			void parse (lambda_p::tokens::token * token) override;
			void parse_expression (lambda_p::tokens::token * token);
			void parse_local_name (lambda_p::tokens::token * token);
			void parse_full_name (lambda_p::tokens::token * token);
			void parse_nested (lambda_p::tokens::token * token);
		};
	}
}

