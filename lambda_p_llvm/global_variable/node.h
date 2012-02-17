#pragma once

#include <lambda_p_llvm/global_value/node.h>

namespace llvm
{
	class GlobalVariable;
}
namespace lambda_p_llvm
{
	namespace global_variable
	{
		class node : public lambda_p_llvm::global_value::node
		{
		public:
			node (llvm::GlobalVariable * value_a, boost::shared_ptr <lambda_p_llvm::type::node> type_a);
			llvm::GlobalVariable * global_variable ();
			boost::shared_ptr <lambda_p_llvm::type::node> type;
		};
	}
}

