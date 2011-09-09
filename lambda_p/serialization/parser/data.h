#pragma once

#include <lambda_p/serialization/parser/state.h>
#include <lambda_p/serialization/parser/statement.h>

namespace lambda_p
{
	namespace serialization
	{
		namespace parser
		{
			class data : public state
			{
			public:
				data (::boost::shared_ptr < ::lambda_p::serialization::parser::statement> statement_a);
				~data (void);
				state_id state_type ();
				::boost::shared_ptr < ::lambda_p::core::routine> & routine ();
				::boost::shared_ptr < ::lambda_p::serialization::parser::statement> statement;
			};
		}
	}
}

