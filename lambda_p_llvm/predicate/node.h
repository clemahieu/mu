#pragma once

#include <lambda_p/node.h>

#include <llvm/Instructions.h>

namespace lambda_p_llvm
{
	namespace predicate
	{
		class node : public lambda_p::node
		{
		public:
			node (llvm::CmpInst::Predicate value_a);
			llvm::CmpInst::Predicate value;
		};
	}
}

