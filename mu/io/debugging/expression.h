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
			class node;
			class expression
			{
				mu::core::context context;
				mu::io::debugging::routine * routine;
				std::vector <mu::io::debugging::node *> dependencies;
			};
		}
	}
}