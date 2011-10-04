#pragma once

#include <lambda_p/parser/state.h>
#include <lambda_p/parser/statement.h>

namespace lambda_p
{
	namespace parser
	{
		class reference : public state
		{
		public:
			reference (::std::wstring target_statement_a);
			~reference (void);
			state_id state_type ();
			::std::wstring target_statement;
		};
	}
}

