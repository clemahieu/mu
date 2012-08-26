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
			class extension : public mu::io::keywording::state
			{
			public:
				extension (mu::io::keywording::keywording & keywording_a, mu::llvm_::module::node * module_a);
                void operator () (mu::io::tokens::token * token_a) override;
				mu::llvm_::module::node * module;
                mu::io::keywording::keywording & keywording;
                bool have_keyword;
			};
		}
	}
}
