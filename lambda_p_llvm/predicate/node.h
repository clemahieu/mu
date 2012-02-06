#pragma once

#include <llvm/Instructions.h>

namespace lambda_p_llvm
{
	namespace predicate
	{
		class node
		{
		public:
			llvm::CmpInst::Predicate value;
		};
	}
}

