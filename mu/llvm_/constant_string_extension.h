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
			class extension : public mu::io::analyzer::state
			{
			public:
				extension (mu::io::analyzer::analyzer & analyzer_a, mu::llvm_::module::node * module_a);
                void operator () (mu::io::tokens::token const & token_a) override;
				mu::llvm_::module::node * module;
                mu::io::analyzer::analyzer & analyzer;
                bool have_keyword;
			};
		}
	}
}
