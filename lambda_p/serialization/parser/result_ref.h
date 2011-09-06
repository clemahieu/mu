#pragma once

#include <lambda_p/serialization/parser/state.h>
#include <lambda_p/serialization/parser/statement.h>

namespace lambda_p
{
	namespace serialization
	{
		namespace parser
		{
			class result_ref : state
			{
			public:
				result_ref (::std::wstring target_statement_a, ::lambda_p::serialization::parser::statement * statement_a);
				~result_ref (void);
				state_id state_type ();
				::std::wstring target_statement;
				::lambda_p::serialization::parser::statement * statement;
			};
		}
	}
}

