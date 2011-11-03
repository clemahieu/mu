#pragma once

#include <lambda_p/binder/node.h>

namespace llvm
{
	class Module;
}
namespace lambda_p_llvm
{
	class module : public lambda_p::binder::node
	{
	public:
		module (llvm::Module * module_a);
		llvm::Module * module_m;
	};
}
