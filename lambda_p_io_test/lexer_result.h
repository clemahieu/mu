#pragma once

#include <lambda_p/context.h>

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
		void operator () (lambda_p_io::tokens::token *, lambda_p::context context_a);
		std::vector <std::pair <lambda_p_io::tokens::token *, lambda_p::context>> results;
	};
}

