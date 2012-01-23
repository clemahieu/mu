#pragma once

#include <lambda_p_llvm/type/node.h>

namespace llvm
{
	class PointerType;
}
namespace lambda_p_llvm
{
	namespace pointer_type
	{
		class node : public lambda_p_llvm::type::node
		{
		public:
			node (llvm::PointerType * type_a);
			llvm::PointerType * pointer_type ();
		};
	}
}


