#pragma once

#include <mu/io/debugging/context.h>

#include <boost/function.hpp>

namespace mu
{
	namespace core
	{
		class node;
        class node_list;
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
				resolver (mu::core::node_list & target_a, mu::io::debugging::context const & context_a);
				void operator () (mu::core::errors::error_target & errors, bool global, mu::io::debugging::context const & context_a, mu::core::node * node_a);
                mu::core::node_list & target;
                mu::io::debugging::context context;
                bool only_global;
			};
		}
	}
}

