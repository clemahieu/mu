#pragma once

#include <boost/shared_ptr.hpp>

#include <lambda_p/parser/state.h>
#include <map>
#include <string>
#include <vector>

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
	}
	namespace tokens
	{
		class identifier;
	}
	namespace parser
	{
		class parser;
		class routine : public state
		{
		public:
			routine (lambda_p::parser::parser & parser_a, boost::function <void (boost::shared_ptr <lambda_p::core::routine> routine)> target_a, std::vector <std::pair <std::wstring, boost::shared_ptr <lambda_p::binder::node>>> & injected_parameters, std::vector <std::wstring> & injected_returns);
			void parse (lambda_p::tokens::token * token) override;
			void reset ();
			void routine_expression_sink (lambda_p::core::expression * expression);
			void surface_sink (lambda_p::tokens::identifier * identifier);
			lambda_p::parser::parser & parser;
			bool have_surface;
			std::vector <lambda_p::core::expression *> surface;
			std::multimap <std::wstring, std::pair <lambda_p::core::expression *, size_t>> unresolved_references;
			std::map <std::wstring, lambda_p::core::expression *> names;
			boost::function <void (boost::shared_ptr <lambda_p::core::routine> routine)> target;
		};
	}
}

