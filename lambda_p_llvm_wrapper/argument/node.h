#pragma once

#include <lambda_p_llvm_wrapper/value/node.h>

namespace llvm
{
	class Argument;
}
namespace lambda_p_llvm_wrapper
{
	namespace argument
	{
		class node : public lambda_p_llvm_wrapper::value::node
		{
		public:
			node (llvm::Argument * argument_a);
			llvm::Argument * argument ();
		};
	}
}

