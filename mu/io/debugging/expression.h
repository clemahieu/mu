#pragma once

#include <mu/io/debugging/context.h>
#include <mu/io/debugging/node.h>

#include <vector>

namespace mu
{
	namespace io
	{
		namespace debugging
		{
			class routine;
			class node;
			class expression : public mu::io::debugging::node
			{
			public:
				std::vector <boost::shared_ptr <mu::io::debugging::node>> dependencies;
			};
		}
	}
}