#pragma once

#include <mu/core/context.h>

#include <vector>

namespace mu
{
	namespace io
	{
		namespace debugging
		{
			class routine;
			class node
			{
			public:
				node ();
				node (mu::core::context context_a);
				mu::core::context context;
				mu::io::debugging::routine * routine;
			};
		}
	}
}