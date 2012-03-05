#pragma once

#include <boost/shared_ptr.hpp>

namespace mu
{
	namespace llvm_
	{
		namespace basic_block
		{
			class node;
		}
		namespace context
		{
			class node;
		}
		namespace module
		{
			class node;
		}
		namespace analyzer
		{
			class context
			{
			public:
				boost::shared_ptr <mu::llvm_::context::node> context_m;
				boost::shared_ptr <mu::llvm_::module::node> module;
				boost::shared_ptr <mu::llvm_::basic_block::node> block;
			};
		}
	}
}
