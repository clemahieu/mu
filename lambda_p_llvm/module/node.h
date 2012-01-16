#pragma once

#include <lambda_p/node.h>

namespace llvm
{
	class Module;
}
namespace lambda_p_llvm
{
	namespace module
	{
		class node : public lambda_p::node
		{
		public:
			node (llvm::Module * module_a);
			llvm::Module * module;
		};
	}
}

