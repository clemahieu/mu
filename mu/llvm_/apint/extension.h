#pragma once

#include <mu/io/analyzer/extensions/extension.h>

namespace mu
{
	namespace llvm_
	{
		namespace apint
		{
			class extension : public mu::io::analyzer::extensions::extension
			{
			public:
				void operator () (mu::core::errors::error_target * errors_a, mu::io::analyzer::expression & expression_a) override;
			};
		}
	}
}
