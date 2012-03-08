#pragma once

#include <mu/script/fixed.h>
#include <mu/llvm_/basic_block/node.h>

namespace mu
{
	namespace llvm_
	{
		namespace istore
		{
			class operation : public mu::script::fixed
			{
			public:
				operation (boost::shared_ptr <mu::llvm_::basic_block::node> block_a);
				void operator () (mu::script::context & context_a) override;
				size_t count () override;
				boost::shared_ptr <mu::llvm_::basic_block::node> block;
			};
		}
	}
}

