#pragma once

#include <lambda_p_llvm/value/node.h>

namespace llvm
{
	class Instruction;
}
namespace lambda_p_llvm
{
	namespace instruction
	{
		class node : public lambda_p_llvm::value::node
		{
		public:
			node (llvm::Instruction * instruction_a, boost::shared_ptr <lambda_p_llvm::type::node> type_a);
			llvm::Instruction * instruction ();
		};
	}
}

