#pragma once

#include <lambda_p_io/analyzer/extensions/extension.h>

namespace lambda_p_llvm
{
	namespace context
	{
		class node;
	}
	namespace constant_int
	{
		class extension : public lambda_p_io::analyzer::extensions::extension
		{
		public:
			extension (boost::shared_ptr <lambda_p_llvm::context::node> context_a);
			void operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p_io::analyzer::expression & expression_a) override;
			boost::shared_ptr <lambda_p_llvm::context::node> context;
		};
	}
}

