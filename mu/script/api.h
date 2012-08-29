#pragma once

#include <mu/core/types.h>

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
            auto core () -> mu::script::parser_scope::node *;
			auto full () -> mu::script::parser_scope::node *;
            auto loadb_extension () -> mu::core::node *;
            auto loads_extension () -> mu::core::node *;
            mu::core::node * context_extension (mu::script::parser_scope::node * core_a);
		}
	}
}