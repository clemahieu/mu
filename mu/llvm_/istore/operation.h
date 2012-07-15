#pragma once

#include <mu/script/operation.h>
#include <mu/llvm_/basic_block/node.h>

namespace mu
{
	namespace llvm_
	{
		namespace istore
		{
			class operation : public mu::script::operation
			{
			public:
				operation (mu::llvm_::basic_block::node * block_a);
				bool operator () (mu::script::context & context_a) override;
				mu::llvm_::basic_block::node * block;
			};
		}
	}
}

