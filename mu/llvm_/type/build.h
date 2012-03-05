#pragma once

#include <boost/shared_ptr.hpp>

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
				build (boost::shared_ptr <mu::llvm_::context::node> context_a, llvm::Type * type_a);
				boost::shared_ptr <mu::llvm_::type::node> type;
			};
		}
	}
}
