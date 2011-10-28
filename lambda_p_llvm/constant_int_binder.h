#pragma once

#include <lambda_p/binder/binder.h>

namespace lambda_p
{
	namespace binder
	{
		class data;
		class node_list;
	}
}
namespace lambda_p_llvm
{
	class generation_context;
	class constant_int_binder : public lambda_p::binder::binder
	{
	public:
		constant_int_binder (lambda_p_llvm::generation_context & context_a);
		~constant_int_binder (void);
		void bind (lambda_p::core::statement * statement, lambda_p::binder::node_list & nodes, lambda_p::errors::error_list & problems) override;
		std::wstring binder_name () override;
	private:
		lambda_p_llvm::generation_context & context;
	};
}

