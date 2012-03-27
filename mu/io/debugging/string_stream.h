#pragma once

#include <mu/io/debugging/stream.h>

#include <string>

namespace mu
{
	namespace io
	{
		namespace debugging
		{
			class string_stream : public mu::io::debugging::stream
			{
			public:
				std::wstring contents;
			};
		}
	}
}