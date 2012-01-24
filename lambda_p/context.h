#pragma once

#include <lambda_p/position.h>

#include <string>

namespace lambda_p
{
	class context
	{
	public:
		context ();
		context (lambda_p::position first_a, lambda_p::position last_a);
		context (size_t first_row, size_t first_column, size_t first_character, size_t last_row, size_t last_column, size_t last_character);
		std::wstring string ();
		bool operator == (lambda_p::context const & other);
		lambda_p::position first;
		lambda_p::position last;
	};
}

