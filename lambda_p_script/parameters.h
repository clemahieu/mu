#pragma once

#include <lambda_p_script/node.h>

namespace lambda_p_script
{
	class parameters : public lambda_p_script::node
	{
	public:
		void operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, lambda_p_script::context & context, std::vector <boost::shared_ptr <mu::core::node>> & target) override;
	};
}

