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
	namespace script
	{
		namespace astring
		{
			class extension : public mu::io::analyzer::state
			{
			public:
                extension (mu::io::analyzer::analyzer & analyzer_a);
                void operator () (mu::io::tokens::token const & token_a) override;
                static bool const dominating = true;
                mu::io::analyzer::analyzer & analyzer;
			};
		}
	}
}
