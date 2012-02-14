#pragma once

#include <lambda_p/node.h>

#include <llvm/GlobalValue.h>

namespace lambda_p_llvm
{
	namespace linkage_types
	{
		class node : public lambda_p::node
		{
		public:
			node (llvm::GlobalValue::LinkageTypes type_a);
			llvm::GlobalValue::LinkageTypes type;
		};
	}
}

