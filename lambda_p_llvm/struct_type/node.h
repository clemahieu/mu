#pragma once

#include <lambda_p_llvm/type/node.h>

namespace llvm
{
	class StructType;
}
namespace lambda_p_llvm
{
	namespace struct_type
	{
		class node : public lambda_p_llvm::type::node
		{
		public:
			node (llvm::StructType * type_a);
			llvm::StructType * structure_type ();
		};
	}
}

