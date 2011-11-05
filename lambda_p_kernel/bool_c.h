#pragma once

#include <lambda_p/binder/node.h>

namespace lambda_p_kernel
{
	class bool_c : public lambda_p::binder::node
	{
	public:
		bool_c ();
		bool_c (bool value_a);
		bool value;
	};
}

