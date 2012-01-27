#pragma once

#include <lambda_p_llvm/type/node.h>

namespace llvm
{
	class ArrayType;
}
namespace lambda_p_llvm
{
	namespace array_type
	{
		class node : public lambda_p_llvm::type::node
		{
		public:
			node (llvm::ArrayType * type_a);
			llvm::ArrayType * array_type ();
		};
	}
}

