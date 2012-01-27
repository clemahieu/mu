#pragma once

#include <lambda_p_llvm/value/node.h>

namespace llvm
{
	class Constant;
}
namespace lambda_p_llvm
{
	namespace constant
	{
		class node : public lambda_p_llvm::value::node
		{
		public:
			node (llvm::Constant * constant_a);
			llvm::Constant * constant ();
		};
	}
}
