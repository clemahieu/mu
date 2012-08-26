#pragma once

#include <mu/io/position.h>
#include <mu/core/types.h>

namespace mu
{
	namespace io
	{
        class context
        {
        public:
            context ();
            context (mu::io::position first_a, mu::io::position last_a);
            context (size_t first_row, size_t first_column, size_t first_character, size_t last_row, size_t last_column, size_t last_character);
            mu::string string () const;
            bool operator == (mu::io::context const & other) const;
            mu::io::position first;
            mu::io::position last;
        };
	}
}


