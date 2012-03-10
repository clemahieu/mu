#pragma once

#include <mu/core/segment.h>

#include <vector>

#include <boost/shared_ptr.hpp>

namespace mu
{
	namespace core
	{
		class node;
	}
	namespace script
	{
		namespace cluster
		{
			class node;
		}
		namespace runtime
		{
			class frame
			{
			public:
				frame (boost::shared_ptr <mu::core::node> parameters_a, size_t size);
				boost::shared_ptr <mu::core::node> parameters;
				std::vector <std::vector <boost::shared_ptr <mu::core::node>>> nodes;
			};
		}
	}
}

