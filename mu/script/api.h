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
		namespace parser_scope
		{
			class node;
		}
		namespace api
		{
            auto core () -> boost::tuple <mu::script::parser_scope::node *, mu::map <mu::string, mu::core::node *>>;
			auto full () -> boost::tuple <mu::script::parser_scope::node *, mu::map <mu::string, mu::core::node *>>;
            auto loadb_extension () -> mu::core::node *;
            auto loads_extension () -> mu::core::node *;
            mu::core::node * context_extension (mu::script::parser_scope::node * core_a);
		}
	}
}