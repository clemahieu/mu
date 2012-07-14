#pragma once

#include <mu/llvm_/value/node.h>

namespace llvm
{
	class Argument;
}
namespace mu
{
	namespace llvm_
	{
		namespace argument
		{
			class node : public mu::llvm_::value::node
			{
			public:
				node (llvm::Argument * argument_a, mu::llvm_::type::node * type_a);
				llvm::Argument * argument ();
			};
		}
	}
}
