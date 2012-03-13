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
				union
				{
					uint64_t int64s [2];
					uint32_t int32s [4];
					uint8_t bytes [16];
				} value;
			};
		}
	}
}