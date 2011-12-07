#pragma once

#include <lambda_p/parser/state.h>
#include <lambda_p/parser/routine_state.h>

#include <map>
#include <string>
#include <vector>

#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>

namespace lambda_p
{
	namespace binder 
	{
		class node;
	}
	namespace core
	{
		class routine;
		class expression;
		class expression_list;
	}
	namespace tokens
	{
		class identifier;
	}
	namespace parser
	{
		class parser;
		class expression;
		class routine : public state
		{
		public:
			routine (lambda_p::parser::parser & parser_a, boost::function <void (boost::shared_ptr <lambda_p::core::routine> routine)> target_a);
			void parse (lambda_p::tokens::token * token) override;
			void reset ();
			void routine_expression_sink (lambda_p::core::expression * expression);
			lambda_p::parser::parser & parser;
			lambda_p::parser::routine_state::routine_state state;
			boost::shared_ptr <lambda_p::core::routine> routine_m;
			std::multimap <std::wstring, std::pair <boost::shared_ptr <lambda_p::parser::expression>, size_t>> unresolved_references;
			std::map <std::wstring, lambda_p::core::expression *> names;
			boost::function <void (boost::shared_ptr <lambda_p::core::routine> routine)> target;
		};
	}
}

