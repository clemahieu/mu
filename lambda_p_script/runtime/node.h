#pragma once

#include <vector>

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	class node;
	namespace errors
	{
		class error_target;
	}
}
namespace lambda_p_script
{
	namespace runtime
	{
		class context;
		class node
		{
		public:
			virtual void operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p_script::runtime::context & context, std::vector <boost::shared_ptr <lambda_p::node>> & target) = 0;
		};
	}
}

