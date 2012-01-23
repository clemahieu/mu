#pragma once

#include <lambda_p_llvm/pointer_type/node.h>

namespace llvm
{
	class PointerType;
}
namespace lambda_p_llvm
{
	namespace function_pointer_type
	{
		class node : public lambda_p_llvm::pointer_type::node
		{
		public:
			node (llvm::PointerType * function_type_a, bool multiple_return_a);
			llvm::PointerType * function_type ();
			bool multiple_return;
		};
	}
}

