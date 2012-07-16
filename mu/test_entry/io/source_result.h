#pragma once

#include <mu/io/source.h>

#include <vector>

namespace mu
{
	namespace io_test
	{
		class source_result : mu::io::source
		{
		public:
			using mu::io::source::operator ();
			void operator () (char32_t char_a) override;
			std::vector <char32_t> results;
		};
	}
}
