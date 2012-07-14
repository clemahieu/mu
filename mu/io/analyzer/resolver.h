#pragma once

#include <boost/shared_ptr.hpp>

namespace mu
{
	namespace core
	{
		class expression;
		class node;
	}
	namespace io
	{
		namespace debugging
		{
			class expression;
			class node;
		}
		namespace analyzer
		{
			class resolver
			{
			public:
				resolver (mu::core::expression * unresolved_a, size_t position_a);
				void operator () (mu::core::node * node_a);
				mu::core::expression * unresolved;
				size_t position;
			};
		}
	}
}

