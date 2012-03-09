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
				split_return (boost::shared_ptr <mu::llvm_::basic_block::node> block_a, boost::shared_ptr <mu::script::operation> next_a);
				void operator () (mu::script::context & context_a) override;
				boost::shared_ptr <mu::script::operation> next;
				boost::shared_ptr <mu::llvm_::basic_block::node> block;
			};
		}
	}
}
