#pragma once

#include <lambda_p/position.h>

namespace lambda_p
{
	class context
	{
	public:
		context (lambda_p::position first_a, lambda_p::position last_a);
		lambda_p::position first;
		lambda_p::position last;
	};
}

