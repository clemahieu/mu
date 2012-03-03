#pragma once

#include <mu/llvm_/value.node.h>

namespace llvm
{
	class Instruction;
}
namespace mu
{
	namespace llvm_
	{
		namespace instruction
		{
			class node : public mu::llvm_::value::node
			{
			public:
				node (llvm::Instruction * instruction_a, boost::shared_ptr <mu::llvm_::type::node> type_a);
				llvm::Instruction * instruction ();
			};
		}
	}
}
