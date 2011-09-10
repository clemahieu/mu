#pragma once

#include <lambda_p/parser/state.h>

namespace lambda_p
{
	namespace parser
	{
		class node_list : public ::lambda_p::parser::state
		{
		public:
			node_list(void);
			~node_list(void);
			state_id state_type ();
		};
	}
}
