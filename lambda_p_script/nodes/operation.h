#pragma once

#include <lambda_p/node.h>

#include <boost/shared_ptr.hpp>

namespace lambda_p_script
{
	class operation;
	namespace nodes
	{
		class operation : public lambda_p::node
		{
		public:
			operation (size_t parameter_size_a, size_t result_size_a, boost::shared_ptr <lambda_p_script::operation> operation_a);
			size_t parameter_size ();
			size_t result_size ();
			boost::shared_ptr <lambda_p_script::operation> operation_m;
		};
	}
}
