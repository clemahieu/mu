#pragma once

#include <lambda_p_llvm/constant/node.h>

namespace llvm
{
	class ConstantInt;
}
namespace lambda_p_llvm
{
	namespace constant_int
	{
		class node : public lambda_p_llvm::constant::node
		{
		public:
			node (llvm::ConstantInt * constant_int_a);
			llvm::ConstantInt * constant_int ();
		};
	}
}

