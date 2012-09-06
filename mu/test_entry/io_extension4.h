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
		class extension4 : public mu::io::analyzer::state
		{
		public:
            extension4 (mu::io::analyzer::analyzer & analyzer_a);
            void operator () (mu::io::tokens::token const & token_a) override;
            static bool const dominating = false;
            bool first;
            mu::io::analyzer::analyzer & analyzer;
		};
	}
}
