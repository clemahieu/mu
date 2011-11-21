#pragma once

#include <lambda_p/parser/state.h>

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	namespace parser
	{
		class routine;
		class data_target;
		class parser;
		class data : public state
		{
		public:
			data (lambda_p::parser::parser & parser_a, lambda_p::parser::routine & routine_a, lambda_p::parser::data_target & target_a);
			void parse (lambda_p::tokens::token * token) override;
			lambda_p::parser::routine & routine;
			lambda_p::parser::data_target & target;
			lambda_p::parser::parser & parser;
		};
	}
}

