#pragma once

#include <mu/script/operation.h>

namespace mu
{
	namespace llvm_
	{
		namespace basic_block
		{
			class node;
		}
		namespace ccall
		{
			class operation : public mu::script::operation
			{
			public:
				operation (boost::shared_ptr <mu::llvm_::basic_block::node> block_a, boost::shared_ptr <mu::script::operation> call_a);
				bool operator () (mu::script::context & context_a) override;
				boost::shared_ptr <mu::llvm_::basic_block::node> block;
				boost::shared_ptr <mu::script::operation> call;
			};
		}
	}
}
