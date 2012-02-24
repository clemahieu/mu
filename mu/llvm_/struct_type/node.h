#pragma once

#include <mu/llvm_/type/node.h>

#include <vector>

#include <boost/shared_ptr.hpp>

namespace llvm
{
	class StructType;
}
namespace mu
{
	namespace llvm_
	{
		namespace context
		{
			class node;
		}
		namespace struct_type
		{
			class node : public mu::llvm_::type::node
			{
			public:
				node (boost::shared_ptr <mu::llvm_::context::node> context_a, llvm::StructType * struct_type_a);
				node (boost::shared_ptr <mu::llvm_::context::node> context_a);
				node (boost::shared_ptr <mu::llvm_::context::node> context_a, std::vector <boost::shared_ptr <mu::llvm_::type::node>> elements_a);
				llvm::Type * type () override;
				llvm::StructType * struct_type ();
				boost::shared_ptr <mu::llvm_::context::node> context;
				std::vector <boost::shared_ptr <mu::llvm_::type::node>> elements;
			};
		}
	}
}
