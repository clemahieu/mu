#pragma once

#include <mu/io/analyzer/extensions/extension.h>

namespace mu
{
	namespace llvm_
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
				extension (mu::llvm_::module::node * module_a);
                bool operator () () override;
				void operator () (mu::core::errors::error_target * errors_a, mu::io::analyzer::expression & expression_a, mu::string remaining) override;
				mu::llvm_::module::node * module;
			};
		}
	}
}
