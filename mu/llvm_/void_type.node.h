#pragma once

#include <mu/llvm_/type.node.h>

#include <boost/shared_ptr.hpp>

namespace mu
{
	namespace llvm_
	{
		namespace context
		{
			class node;
		}
		namespace void_type
		{
			class node : public mu::llvm_::type::node
			{
			public:
				node (boost::shared_ptr <mu::llvm_::context::node> context_a);
                llvm::Type * type () override;
                llvm::Type * type_m;
			};
		}
	}
}
