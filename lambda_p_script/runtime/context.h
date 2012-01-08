#pragma once

#include <vector>

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	class node;
}
namespace lambda_p_script
{
	namespace runtime
	{
		class context
		{
		public:
			context (size_t size);
			std::vector <std::vector <boost::shared_ptr <lambda_p::node>>> nodes;
		};
	}
}

