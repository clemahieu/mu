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
	namespace io_test
	{
		class extension2 : public mu::io::keywording::state
		{
		public:
            extension2 (mu::io::keywording::keywording & keywording_a);
            void operator () (mu::io::tokens::token * token_a) override;
            static bool const dominating = false;
            mu::io::keywording::keywording & keywording;
		};
	}
}
