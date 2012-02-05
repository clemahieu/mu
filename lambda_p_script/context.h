#pragma once

#include <lambda_p/segment.h>

#include <vector>

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	class node;
}
namespace lambda_p_script
{
	class context
	{
	public:
		context (boost::shared_ptr <lambda_p::node> parameters_a, size_t size);
		boost::shared_ptr <lambda_p::node> parameters;
		std::vector <std::vector <boost::shared_ptr <lambda_p::node>>> nodes;
	};
}

