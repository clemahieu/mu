#pragma once

#include <lambda_p_script/operation.h>
#include <lambda_p_llvm/execution_engine/node.h>

namespace lambda_p_llvm
{
	namespace execution_engine
	{
		class run_function : public lambda_p_script::operation
		{
		public:
			void perform (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p_script::segment <boost::shared_ptr <lambda_p::node>> parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results) override;
			std::wstring name () override;
		};
	}
}

