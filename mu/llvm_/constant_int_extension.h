#pragma once

#include <mu/io/keywording_state.h>

namespace mu
{
    namespace io
    {
        namespace keywording
        {
            class keywording;
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
			class extension : public mu::io::keywording::state
			{
			public:
				extension (mu::io::keywording::keywording & keywording_a, mu::llvm_::context::node * context_a);
                void operator () (mu::io::tokens::token * token_a) override;
				mu::llvm_::context::node * context;
                mu::io::keywording::keywording & keywording;
                bool have_keyword;
                bool have_bits;
                unsigned long long bits;
			};
		}
	}
}
