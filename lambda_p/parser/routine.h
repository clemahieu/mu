#pragma once

#include <boost/shared_ptr.hpp>

#include <lambda_p/parser/state.h>
#include <map>
#include <string>
#include <vector>

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
			routine (lambda_p::parser::parser & parser_a, std::vector <std::pair <std::wstring, boost::shared_ptr <lambda_p::binder::node>>> & injected_parameters, std::vector <std::wstring> & injected_returns);
			void parse (lambda_p::tokens::token * token) override;
			boost::shared_ptr <lambda_p::core::routine> routine_m;
			bool have_surface;
			std::multimap <std::wstring, boost::function <void (size_t)>> unresolved_references;
			std::map <std::wstring, lambda_p::core::expression *> names;
			void surface_sink (lambda_p::tokens::identifier * identifier);
			bool parsed_routine;
			lambda_p::parser::parser & parser;
		};
	}
}

