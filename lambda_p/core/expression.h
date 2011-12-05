#pragma once

#include <vector>

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	namespace core
	{
		class expression
		{
		public:
			std::vector <lambda_p::core::expression *> contents;
		};
	}
}
