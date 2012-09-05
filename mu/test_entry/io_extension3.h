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
	namespace io_test
	{
		class extension3 : public mu::io::analyzer::state
		{
		public:
            extension3 (mu::io::analyzer::analyzer & analyzer_a);
            void operator () (mu::io::tokens::token * token_a) override;
            static bool const dominating = false;
            mu::io::analyzer::analyzer & analyzer;
		};
	}
}
