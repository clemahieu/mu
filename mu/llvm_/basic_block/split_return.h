#pragma once

#include <mu/script/operation.h>

namespace mu
{
	namespace llvm_
	{
		namespace basic_block
		{
			class node;
			class split_return : public mu::script::operation
			{
			public:
				split_return (mu::llvm_::basic_block::node * block_a, mu::script::operation * next_a);
				bool operator () (mu::script::context & context_a) override;
				mu::script::operation * next;
				mu::llvm_::basic_block::node * block;
			};
		}
	}
}
