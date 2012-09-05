#pragma once

#include <mu/io/analyzer_state.h>

namespace mu
{
    namespace io
    {
        namespace analyzer
        {
            class analyzer;
        }
    }
	namespace llvm_
	{
		namespace context
		{
			class node;
		}
		namespace constant_int
		{
			class extension : public mu::io::analyzer::state
			{
			public:
				extension (mu::io::analyzer::analyzer & analyzer_a, mu::llvm_::context::node * context_a);
                void operator () (mu::io::tokens::token * token_a) override;
				mu::llvm_::context::node * context;
                mu::io::analyzer::analyzer & analyzer;
                bool have_keyword;
                bool have_bits;
                unsigned long long bits;
			};
		}
	}
}
