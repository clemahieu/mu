#pragma once

#include <mu/core/context.h>
#include <mu/io/debugging/hash.h>
#include <mu/io/debugging/node.h>

#include <vector>

namespace mu
{
	namespace io
	{
		namespace debugging
		{
			class expression;
			class cluster;
			class routine : public mu::io::debugging::node
			{
			public:
				mu::io::debugging::cluster * cluster;
				mu::io::debugging::expression * body;
			};
		}
	}
}