#pragma once

#include <lambda_p/parser/state.h>

#include <boost/function.hpp>

namespace lambda_p
{
	namespace tokens
	{
		class identifier;
	}
	namespace parser
	{
		class parser;
		class identifier_list : public lambda_p::parser::state
		{
		public:
			identifier_list (lambda_p::parser::parser & parser_a, boost::function <void (lambda_p::tokens::identifier *)> target_a);
			void parse (lambda_p::tokens::token * token) override;
			boost::function <void (lambda_p::tokens::identifier *)> target;
			lambda_p::parser::parser & parser;
		};
	}
}

