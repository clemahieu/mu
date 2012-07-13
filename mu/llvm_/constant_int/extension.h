#pragma once

#include <mu/io/analyzer/extensions/extension.h>

namespace mu
{
	namespace llvm_
	{
		namespace context
		{
			class node;
		}
		namespace constant_int
		{
			class extension : public mu::io::analyzer::extensions::extension
			{
			public:
				extension (boost::shared_ptr <mu::llvm_::context::node> context_a);
				void operator () (mu::core::errors::error_target * errors_a, mu::io::analyzer::expression & expression_a) override;
				boost::shared_ptr <mu::llvm_::context::node> context;
			};
		}
	}
}
