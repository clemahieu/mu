#pragma once

#include <mu/core/node.h>

#include <llvm/ExecutionEngine/GenericValue.h>

namespace lambda_p_llvm
{
	namespace execution_engine
	{
		namespace generic_value
		{
			class node : public mu::core::node
			{
			public:
				node ();
				node (llvm::GenericValue & value_a);
				std::wstring debug () override;
				llvm::GenericValue value;
			};
		}
	}
}

