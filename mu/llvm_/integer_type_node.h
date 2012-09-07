#pragma once

#include <mu/llvm_/type_node.h>

namespace llvm
{
	class IntegerType;
}
namespace mu
{
	namespace llvm_
	{
		namespace integer_type
		{
			class node : public mu::llvm_::type::node
			{
			public:
				node (llvm::IntegerType * type_a);
				llvm::Type * type () override;
				llvm::IntegerType * integer_type ();
				llvm::IntegerType * type_m;
			};
		}
	}
}
