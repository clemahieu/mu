#pragma once

namespace llvm
{
	class Type;
}
namespace mu
{
	namespace llvm_
	{
		namespace context
		{
			class node;
		}
		namespace type
		{
			class node;
			class build
			{
			public:
				build (mu::llvm_::context::node * context_a, llvm::Type * type_a);
				mu::llvm_::type::node * type;
			};
		}
	}
}
