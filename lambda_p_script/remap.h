#pragma once

#include <lambda_p_script/node.h>

namespace lambda_p
{
	class routine;
}
namespace lambda_p_script
{
	class remap : public lambda_p_script::node
	{
	public:
		remap (boost::shared_ptr <lambda_p::routine> routine_a);
		void operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p_script::context & context, std::vector <boost::shared_ptr <lambda_p::node>> & target) override;
		boost::shared_ptr <lambda_p::routine> routine;
	};
}

