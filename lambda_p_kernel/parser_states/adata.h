#pragma once

#include <lambda_p/parser/state.h>

namespace lambda_p
{
	namespace parser
	{
		class parser;
		class routine;
		class association_target;
	}
}
namespace lambda_p_kernel
{
	namespace parser_states
	{
		class adata : public lambda_p::parser::state
		{
		public:
			adata (lambda_p::parser::parser & parser_a, lambda_p::parser::routine & routine_a, lambda_p::parser::association_target & target_a);
			void parse (lambda_p::tokens::token * token) override;
			lambda_p::parser::parser & parser;
			lambda_p::parser::routine & routine;
			lambda_p::parser::association_target & target;
		};
	}
}

