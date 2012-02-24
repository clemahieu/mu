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
				void operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results) override;
				size_t count () override;
			};
		}
	}
}

