#pragma once

#include <lambda_p/parser/state.h>

#include <string>

namespace lambda_p
{
	namespace parser
	{
		class error : public lambda_p::parser::state
		{
		public:
			error(std::wstring message_a);
			lambda_p::parser::state_id state_type ();
			std::wstring message;
		};
	}
}
