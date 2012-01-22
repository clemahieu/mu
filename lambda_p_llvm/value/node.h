#pragma once

#include <lambda_p/node.h>

namespace llvm
{
	class Value;
}
namespace lambda_p_llvm
{
	namespace value
	{
		class node : public lambda_p::node
		{
		public:
			node (llvm::Value * value_a);
			llvm::Value * value ();
		protected:
			llvm::Value * value_m;
		};
	}
}

