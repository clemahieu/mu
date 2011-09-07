#pragma once

#include <lambda_p/serialization/parser/state.h>
#include <lambda_p/serialization/parser/statement.h>

namespace lambda_p
{
	namespace serialization
	{
		namespace parser
		{
			class declaration : public state
			{
			public:
				declaration (::lambda_p::serialization::parser::statement * statement_a);
				~declaration (void);
				state_id state_type ();
				::lambda_p::serialization::parser::statement * statement;
			};
		}
	}
}

