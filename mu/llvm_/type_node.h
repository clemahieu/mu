#pragma once

#include <mu/core/node.h>

namespace llvm
{
	class Type;
}
namespace mu
{
	namespace llvm_
	{
		namespace type
		{
			class node : public mu::core::node
			{
			public:
				virtual llvm::Type * type () = 0;
			};
		}
	}
}
