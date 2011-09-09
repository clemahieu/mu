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
				data (::lambda_p::serialization::parser::statement * statement_a);
				~data (void);
				state_id state_type ();
				::boost::shared_ptr < ::lambda_p::core::routine> & routine ();
				::lambda_p::serialization::parser::statement * statement;
			};
		}
	}
}

