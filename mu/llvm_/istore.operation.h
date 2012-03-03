#pragma once

#include <mu/script/fixed.h>
#include <mu/llvm_/basic_block.node.h>

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
				void operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results) override;
				size_t count () override;
				boost::shared_ptr <mu::llvm_::basic_block::node> block;
			};
		}
	}
}

