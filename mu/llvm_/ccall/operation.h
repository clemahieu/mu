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
				void perform (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results) override;
				boost::shared_ptr <mu::llvm_::basic_block::node> block;
				boost::shared_ptr <mu::script::operation> call;
			};
		}
	}
}
