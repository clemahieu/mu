#pragma once

#include <mu/core/node.h>

namespace llvm
{
	class Type;
}
namespace lambda_p_llvm
{
	namespace type
	{
		class node : public mu::core::node
		{
		public:
			std::wstring name () override;
			virtual llvm::Type * type () = 0;
		};
	}
}

