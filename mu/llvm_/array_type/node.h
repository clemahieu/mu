#pragma once

#include <mu/llvm_/type/node.h>

#include <boost/shared_ptr.hpp>

namespace llvm
{
	class ArrayType;
}
namespace mu
{
	namespace llvm_
	{
		namespace context
		{
			class node;
		}
		namespace array_type
		{
			class node : public mu::llvm_::type::node
			{
			public:
				node (boost::shared_ptr <mu::llvm_::context::node> context_a, llvm::ArrayType * array_type_a);
				node (boost::shared_ptr <mu::llvm_::type::node> element_a, size_t count_a);
				llvm::Type * type () override;
				llvm::ArrayType * array_type ();
				boost::shared_ptr <mu::llvm_::type::node> element;
				size_t count;
			};
		}
	}
}
