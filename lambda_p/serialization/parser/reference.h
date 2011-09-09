#pragma once

#include <lambda_p/serialization/parser/state.h>
#include <lambda_p/serialization/parser/statement.h>

namespace lambda_p
{
	namespace serialization
	{
		namespace parser
		{
			class reference : public state
			{
			public:
				reference (::std::wstring target_statement_a, ::lambda_p::serialization::parser::statement * statement_a);
				~reference (void);
				state_id state_type ();
				::std::wstring target_statement;
				::boost::shared_ptr < ::lambda_p::core::routine> & routine ();
				::lambda_p::serialization::parser::statement * statement;
			};
		}
	}
}

