#pragma once

#include <vector>

namespace lambda_p_io
{
	namespace tokens
	{
		class token;
	}
}
namespace lambda_p_io_test
{
	class lexer_result
	{
	public:
		void operator () (lambda_p_io::tokens::token *);
		std::vector <lambda_p_io::tokens::token *> results;
	};
}

