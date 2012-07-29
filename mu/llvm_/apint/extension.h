#pragma once

#include <mu/io/keywording/state.h>

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
		namespace apint
		{
			class extension : public mu::io::keywording::state
			{
			public:
                extension (mu::io::keywording::keywording & keywording_a);
                void operator () (mu::io::tokens::token * token_a, mu::io::debugging::context context_a) override;
                static bool const dominating = false;
                mu::io::keywording::keywording & keywording;
			};
		}
	}
}
