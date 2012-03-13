#pragma once

#include <mu/core/context.h>

#include <vector>

namespace mu
{
	namespace io
	{
		namespace debugging
		{
			class expression;
			class node
			{
				mu::core::context context;
				mu::io::debugging::expression * expression;
			};
		}
	}
}