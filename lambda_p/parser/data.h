#pragma once

#include <lambda_p/parser/state.h>
#include <lambda_p/parser/statement.h>

namespace lambda_p
{
	namespace parser
	{
		class data : public state
		{
		public:
			data (::boost::shared_ptr < ::lambda_p::parser::statement> statement_a);
			~data (void);
			state_id state_type ();
			::boost::shared_ptr < ::lambda_p::parser::statement> statement;
		};
	}
}

