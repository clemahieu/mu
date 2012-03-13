#pragma once

#include <mu/core/context.h>
#include <mu/io/debugging/hash.h>

#include <vector>

namespace mu
{
	namespace io
	{
		namespace debugging
		{
			class routine;
			class cluster
			{
				mu::core::context context;
				mu::io::debugging::hash hash;
				wchar_t start [4];
				std::vector <mu::io::debugging::routine *> routines;
			};
		}
	}
}