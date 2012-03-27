#pragma once

#include <boost/cstdint.hpp>

namespace mu
{
	namespace io
	{
		namespace debugging
		{
			class hash
			{
			public:
				union
				{
					uint64_t int64s [4];
					uint32_t int32s [8];
					uint8_t bytes [32];
				} value;
			};
		}
	}
}