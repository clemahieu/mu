#pragma once

#include <lambda_p/node.h>

namespace llvm
{
	class Type;
}
namespace lambda_p_llvm_wrapper
{
	namespace type
	{
		class node : public lambda_p::node
		{
		public:
			node (llvm::Type * type_a);
			llvm::Type * type ();
		protected:
			llvm::Type * type_m;
		};
	}
}

