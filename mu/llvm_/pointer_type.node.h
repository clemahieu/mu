#pragma once

#include <mu/llvm_/type.node.h>

#include <boost/shared_ptr.hpp>

namespace llvm
{
	class PointerType;
}
namespace mu
{
	namespace llvm_
	{
		namespace context
		{
			class node;
		}
		namespace pointer_type
		{
			class node : public mu::llvm_::type::node
			{
			public:
                node (boost::shared_ptr <mu::llvm_::context::node> context_a, llvm::PointerType * pointer_type_a);
				node (boost::shared_ptr <mu::llvm_::type::node> element_a);
                llvm::Type * type () override;
                llvm::PointerType * pointer_type ();
				boost::shared_ptr <mu::llvm_::type::node> element;
			};
		}
	}
}


