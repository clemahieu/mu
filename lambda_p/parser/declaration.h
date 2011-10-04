#pragma once

#include <lambda_p/parser/state.h>
#include <lambda_p/parser/statement.h>

namespace lambda_p
{
	namespace parser
	{
		class declaration : public state
		{
		public:
			declaration (::boost::shared_ptr < ::lambda_p::parser::statement> statement_a);
			~declaration (void);
			state_id state_type ();
			::boost::shared_ptr < ::lambda_p::core::routine> & routine ();
			::boost::shared_ptr < ::lambda_p::parser::statement> statement;
		};
	}
}

