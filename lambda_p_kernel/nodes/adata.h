#pragma once

#include <lambda_p/binder/node.h>

#include <string>

namespace lambda_p_kernel
{
	namespace nodes
	{
		class adata : public lambda_p::binder::node
		{
		public:
			adata (std::string string_a);
			std::string string;
		};
	}
}
