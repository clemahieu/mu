#pragma once

#include <lambda_p/serialization/parser/state.h>
#include <lambda_p/serialization/parser/statement.h>

namespace lambda_p
{
	namespace serialization
	{
		namespace parser
		{
			class hex_data : public state
			{
			public:
				hex_data (::boost::shared_ptr < ::lambda_p::serialization::parser::statement> statement_a);
				~hex_data (void);
				state_id state_type ();
				::boost::shared_ptr < ::lambda_p::serialization::parser::statement> statement;
			};
		}
	}
}

