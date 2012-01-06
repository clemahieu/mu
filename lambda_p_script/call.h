#pragma once

#include <boost/shared_ptr.hpp>

#include <vector>

namespace lambda_p
{
	class node;
}
namespace lambda_p_script
{
	class operation;
	class call
	{
	public:
		call (std::vector <size_t> arguments_a, boost::shared_ptr <lambda_p_script::operation> operation_a);
		std::vector <size_t> arguments;
		boost::shared_ptr <lambda_p_script::operation> operation;
		void operator () (std::vector <boost::shared_ptr <lambda_p::node>> & context, size_t base, size_t open);
	};
}

