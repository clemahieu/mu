#pragma once

#include <lambda_p_script/node.h>

namespace lambda_p_script
{
	// Internal node to link all values of an expression, e.g. the expression [c] that references the `c' in some other [a; b; c]
	class expression : public lambda_p_script::node
	{
	public:
		expression (size_t index_a);
		size_t index;
		void operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, lambda_p_script::context & context, std::vector <boost::shared_ptr <mu::core::node>> & target) override;
	};
}

