#pragma once

#include <lambda_p/node.h>

#include <llvm/ExecutionEngine/GenericValue.h>

namespace lambda_p_llvm_wrapper
{
	namespace execution_engine
	{
		namespace generic_value
		{
			class node : public lambda_p::node
			{
			public:
				node (llvm::GenericValue & value_a);
				std::wstring debug () override;
				llvm::GenericValue value;
			};
		}
	}
}

