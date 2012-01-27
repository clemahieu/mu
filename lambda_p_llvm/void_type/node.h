#pragma once

#include <lambda_p_llvm/type/node.h>

#include <llvm/Type.h>

namespace lambda_p_llvm
{
	namespace void_type
	{
		class node : public lambda_p_llvm::type::node
		{
		public:
			node (llvm::Type * type_a);
		};
	}
}

