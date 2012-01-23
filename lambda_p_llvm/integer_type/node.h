#pragma once

#include <lambda_p_llvm/type/node.h>

namespace llvm
{
	class IntegerType;
}
namespace lambda_p_llvm
{
	namespace integer_type
	{
		class node : public lambda_p_llvm::type::node
		{
		public:
			node (llvm::IntegerType * type_a);
			llvm::IntegerType * integer_type ();
		};
	}
}

