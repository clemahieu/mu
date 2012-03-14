#pragma once

#include <mu/io/debugging/context.h>
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
				boost::shared_ptr <mu::io::debugging::expression> body;
			};
		}
	}
}