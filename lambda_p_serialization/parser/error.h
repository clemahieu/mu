#pragma once

#include <lambda_p_serialization/parser/state.h>

#include <string>

namespace lambda_p_serialization
{
	namespace parser
	{
		class error : public lambda_p_serialization::parser::state
		{
		public:
			error(std::wstring message_a);
			void parse (lambda_p_serialization::tokens::token * token) override;
			std::wstring message;
		};
	}
}
