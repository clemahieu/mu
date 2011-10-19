#pragma once

#include <lambda_p/binder/instance.h>

namespace lambda_p_kernel
{
	class number : public lambda_p::binder::instance
	{
	public:
		number (long long int value_a);
		long long int value;
	};
}

