#pragma once

#include <lambda_p_script/operation.h>

namespace lambda_p_llvm
{
	namespace instructions
	{
		class call : public lambda_p_script::operation
		{
		public:
			void perform (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p::segment <boost::shared_ptr <lambda_p::node>> parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results) override;
		};
	}
}

