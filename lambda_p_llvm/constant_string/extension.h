#pragma once

#include <mu/io/analyzer/extensions/extension.h>

namespace lambda_p_llvm
{
	namespace module
	{
		class node;
	}
	namespace context
	{
		class node;
	}
	namespace constant_string
	{
		class extension : public mu::io::analyzer::extensions::extension
		{
		public:
			extension (boost::shared_ptr <lambda_p_llvm::context::node> context_a, boost::shared_ptr <lambda_p_llvm::module::node> module_a);
			void operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::io::analyzer::expression & expression_a) override;
			boost::shared_ptr <lambda_p_llvm::context::node> context;
			boost::shared_ptr <lambda_p_llvm::module::node> module;
		};
	}
}

