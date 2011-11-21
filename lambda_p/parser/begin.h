#pragma once

#include <lambda_p/parser/state.h>

namespace lambda_p
{	
	namespace parser
	{
		class parser;
		class begin : public state
		{
		public:
			begin (lambda_p::parser::parser & parser_a);
			void parse (lambda_p::tokens::token * token) override;
			lambda_p::parser::parser & parser;
		};
	}
}

