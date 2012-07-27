#pragma once

#include <boost/shared_ptr.hpp>

#include <mu/io/debugging/context.h>

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
				resolver (mu::core::expression & unresolved_a, size_t position_a, mu::io::debugging::context const & context_a);
				void operator () (mu::core::errors::error_target & errors, bool global, mu::io::debugging::context const & context_a, mu::core::node * node_a);
				mu::core::expression & unresolved;
                mu::io::debugging::context context;
				size_t position;
                bool only_global;
			};
		}
	}
}

