#pragma once

#include <vector>

namespace lambda_p_serialization
{
	namespace tokens
	{
		class token;
	}
}
namespace lambda_p_serialization_test
{
	class lexer_result
	{
	public:
		void operator () (lambda_p_serialization::tokens::token *);
		std::vector <lambda_p_serialization::tokens::token *> results;
	};
}

