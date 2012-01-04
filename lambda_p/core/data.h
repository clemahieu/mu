#pragma once

#include <string>

#include <lambda_p/core/node.h>

namespace lambda_p
{
	namespace core
	{
		class data : public lambda_p::core::node
		{
		public:
			data (std::wstring string_a);
			std::wstring string;
		};
	}
}

