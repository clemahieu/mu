#pragma once

#include <lambda_p_script/runtime/node.h>

namespace lambda_p_script
{
	namespace runtime
	{
		class constant : public lambda_p_script::runtime::node
		{
		public:
			constant (boost::shared_ptr <lambda_p::node> value_a);
			void operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p_script::runtime::context & context, std::vector <boost::shared_ptr <lambda_p::node>> & target) override;
			boost::shared_ptr <lambda_p::node> value;
		};
	}
}

