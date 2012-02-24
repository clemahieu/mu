#pragma once

#include <mu/core/node.h>

#include <llvm/Instructions.h>

namespace mu
{
	namespace llvm_
	{
		namespace predicate
		{
			class node : public mu::core::node
			{
			public:
				node (llvm::CmpInst::Predicate value_a);
				llvm::CmpInst::Predicate value;
			};
		}
	}
}
