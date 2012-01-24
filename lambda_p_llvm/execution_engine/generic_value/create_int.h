#pragma once

#include <lambda_p_script/fixed.h>

#include <llvm/ExecutionEngine/GenericValue.h>

namespace lambda_p_llvm
{
	namespace execution_engine
	{
		namespace generic_value
		{
			class create_int : public lambda_p_script::fixed
			{
			public:
				void operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p_script::segment <boost::shared_ptr <lambda_p::node>> parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results) override;
				size_t count () override;
			};
		}
	}
}

