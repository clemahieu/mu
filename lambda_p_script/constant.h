#pragma once

#include <lambda_p_script/node.h>

namespace lambda_p_script
{
	class constant : public lambda_p_script::node
	{
	public:
		constant (boost::shared_ptr <lambda_p::node> value_a);
		void operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p_script::context & context, std::vector <boost::shared_ptr <lambda_p::node>> & target) override;
		boost::shared_ptr <lambda_p::node> value;
	};
}

