#pragma once

#include <mu/core/node.h>

#include <llvm/ExecutionEngine/GenericValue.h>

namespace mu
{
	namespace llvm_
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
					mu::string debug () override;
					llvm::GenericValue value;
				};
			}
		}
	}
}
