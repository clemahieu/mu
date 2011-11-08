#pragma once

#include <lambda_p/binder/binder.h>

namespace llvm
{
	class Type;
}
namespace lambda_p_llvm
{
	class type_inference : public lambda_p::binder::binder
	{
	public:
		type_inference (llvm::Type const * type_a);
		void bind (lambda_p::core::statement * statement, lambda_p::binder::list & nodes, lambda_p::errors::error_list & problems) override;
		std::wstring binder_name () override;
		llvm::Type const * type;
	};
}

