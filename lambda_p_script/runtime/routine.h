#pragma once

#include <lambda_p_script/runtime/context.h>
#include <lambda_p_script/nodes/operation.h>

#include <vector>

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	class node;

namespace lambda_p_script
{
	namespace runtime
	{
		class routine : public lambda_p_script::nodes::operation
		{
		public:
			void operator () (std::vector <boost::shared_ptr <lambda_p::node>> & parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results) override;
			std::vector <boost::shared_ptr <lambda_p_script::nodes::operation>> operations;
		};
	}
}

