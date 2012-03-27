#pragma once

#include <mu/io/debugging/stream.h>

#include <string>

namespace mu
{
	namespace io
	{
		namespace debugging
		{
			class file_stream : public mu::io::debugging::stream
			{
			public:
				std::wstring original_name;
			};
		}
	}
}