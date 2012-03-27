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
				file_stream ();
				file_stream (std::wstring const & original_name_a);
				std::wstring original_name;
			};
		}
	}
}