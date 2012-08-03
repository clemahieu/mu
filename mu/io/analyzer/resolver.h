#pragma once

#include <mu/io/debugging/context.h>

#include <boost/function.hpp>

namespace mu
{
	namespace core
	{
		class expression;
		class node;
        namespace errors
        {
            class error_target;
        }
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
				resolver (boost::function <void (mu::core::node *)> unresolved_a, mu::io::debugging::context const & context_a);
				void operator () (mu::core::errors::error_target & errors, bool global, mu::io::debugging::context const & context_a, mu::core::node * node_a);
				boost::function <void (mu::core::node *)> unresolved;
                mu::io::debugging::context context;
                bool only_global;
			};
		}
	}
}

