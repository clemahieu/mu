#pragma once

#include <mu/core/node.h>

#include <llvm/GlobalValue.h>

namespace mu
{
	namespace llvm_
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
}
