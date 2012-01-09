#pragma once

#include <lambda_p_script/nodes/operation.h>

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
		class call;
		class routine : public lambda_p_script::nodes::operation
		{
		public:
			void operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, std::vector <boost::shared_ptr <lambda_p::node>> & parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results) override;
			std::vector <boost::shared_ptr <lambda_p_script::runtime::call>> calls;
		};
	}
}

