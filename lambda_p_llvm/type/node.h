#pragma once

#include <lambda_p/node.h>

namespace llvm
{
	class Type;
}
namespace lambda_p_llvm
{
	namespace type
	{
		class node : public lambda_p::node
		{
		public:
			virtual llvm::Type * type () = 0;
		};
	}
}

