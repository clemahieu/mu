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
		namespace analyzer
		{
			class resolver
			{
			public:
				resolver (boost::shared_ptr <mu::core::expression> unresolved_a, size_t position_a);
				void operator () (boost::shared_ptr <mu::core::node> node_a);
				boost::shared_ptr <mu::core::expression> unresolved;
				size_t position;
			};
		}
	}
}

