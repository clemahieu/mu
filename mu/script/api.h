#pragma once

#include <mu/core/types.h>

#include <boost/tuple/tuple.hpp>

namespace mu
{
    namespace core
    {
        class node;
    }
	namespace script
	{
		namespace extensions
		{
			class node;
		}
		namespace api
		{
            auto core () -> boost::tuple <mu::script::extensions::node *, mu::map <mu::string, mu::core::node *>>;
			mu::script::extensions::node * full ();
            auto loadb_extension () -> mu::core::node *;
            auto loads_extension () -> mu::core::node *;
            mu::core::node * context_extension (mu::script::extensions::node * core_a);
		}
	}
}