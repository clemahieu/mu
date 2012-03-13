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
				resolver (boost::shared_ptr <mu::core::expression> unresolved_a, mu::io::debugging::expression * unresolved_info_a, size_t position_a);
				void operator () (boost::shared_ptr <mu::core::node> node_a, mu::io::debugging::node * node_info_a);
				boost::shared_ptr <mu::core::expression> unresolved;
				mu::io::debugging::expression * unresolved_info;
				size_t position;
			};
		}
	}
}

