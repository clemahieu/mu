#pragma once

#include <lambda_p_script/runtime/node.h>

namespace lambda_p_script
{
	namespace runtime
	{
		class expression : public lambda_p_script::runtime::node
		{
		public:
			expression (size_t index_a);
			size_t index;
			void operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p_script::runtime::context & context, std::vector <boost::shared_ptr <lambda_p::node>> & target) override;
		};
	}
}

