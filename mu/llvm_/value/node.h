#pragma once

#include <mu/core/node.h>

namespace llvm
{
	class Value;
}
namespace mu
{
	namespace llvm_
	{
		namespace type
		{
			class node;
		}
		namespace value
		{
			class node : public mu::core::node
			{
			public:
				node (llvm::Value * value_a, mu::llvm_::type::node * type_a);
				llvm::Value * value ();
				mu::string name () override;
				mu::llvm_::type::node * type;
			protected:
				llvm::Value * value_m;
			};
		}
	}
}
