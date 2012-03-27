#pragma once

#include <mu/io/debugging/position.h>

#include <string>

#include <boost/shared_ptr.hpp>

namespace mu
{
	namespace io
	{
		namespace debugging
		{
			class stream;
			class context
			{
			public:
				context ();
				context (mu::io::debugging::position first_a, mu::io::debugging::position last_a);
				context (boost::shared_ptr <mu::io::debugging::stream> stream_a, mu::io::debugging::position first_a, mu::io::debugging::position last_a);
				context (size_t first_row, size_t first_column, size_t first_character, size_t last_row, size_t last_column, size_t last_character);
				context (boost::shared_ptr <mu::io::debugging::stream> stream_a, size_t first_row, size_t first_column, size_t first_character, size_t last_row, size_t last_column, size_t last_character);
				std::wstring string ();
				bool operator == (mu::io::debugging::context const & other);
				boost::shared_ptr <mu::io::debugging::stream> stream;
				mu::io::debugging::position first;
				mu::io::debugging::position last;
			};
		}
	}
}


