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
			class expression;
			class cluster;
			class routine
			{
				mu::core::context context;
				mu::io::debugging::hash hash;
				wchar_t start [4];
				mu::io::debugging::cluster * cluster;
				mu::io::debugging::expression * body;
			};
		}
	}
}