#pragma once

#include <lambda_p_llvm/value/node.h>

namespace llvm
{
	class GlobalValue;
}
namespace lambda_p_llvm
{
	namespace type
	{
		class node;
	}
	namespace global_value
	{
		class node : public lambda_p_llvm::value::node
		{
		public:
			node (llvm::GlobalValue * value_a, boost::shared_ptr <lambda_p_llvm::type::node> type_a);
			llvm::GlobalValue * global_value ();
		};
	}
}

