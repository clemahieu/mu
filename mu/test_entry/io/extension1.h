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
	namespace io_test
	{
		class extension1 : public mu::io::keywording::state
		{
		public:
            extension1 (mu::io::keywording::keywording & keywording_a);
            void operator () (mu::io::tokens::token * token_a) override;
            static bool const dominating = false;
            mu::io::keywording::keywording & keywording;
		};
	}
}
