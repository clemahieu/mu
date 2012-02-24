#pragma once

#include <core/node.h>

#include <llvm/GlobalValue.h>

namespace lambda_p_llvm
{
	namespace linkage_types
	{
		class node : public mu::core::node
		{
		public:
			node (llvm::GlobalValue::LinkageTypes type_a);
			llvm::GlobalValue::LinkageTypes type;
		};
	}
}

