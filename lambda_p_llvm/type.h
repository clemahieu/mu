#pragma once

#include <lambda_p/binder/node_instance.h>

#include <llvm/Type.h>

namespace lambda_p_llvm
{
	class type : public ::lambda_p::binder::node_instance
	{
	public:
		type (::llvm::Type const * type_a);
		~type (void);
		::llvm::Type const * type_m;
	};
}

