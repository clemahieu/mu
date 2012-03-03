#pragma once

#include <mu/llvm_/struct_type.node.h>

namespace mu
{
	namespace llvm_
	{
		namespace set_type
		{
			class node : public mu::llvm_::struct_type::node
			{
			public:			
				node (boost::shared_ptr <mu::llvm_::context::node> context_a);
				node (boost::shared_ptr <mu::llvm_::context::node> context_a, std::vector <boost::shared_ptr <mu::llvm_::type::node>> elements_a);
				node (boost::shared_ptr <mu::llvm_::struct_type::node> struct_a);
			};
		}
	}
}
