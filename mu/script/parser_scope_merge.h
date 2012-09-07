#pragma once

#include <mu/script/operation.h>

namespace mu
{
    namespace core
    {
        namespace errors
        {
            class error_target;
        }
    }
	namespace script
	{
        namespace string
        {
            class node;
        }
		namespace parser_scope
		{
            class node;
			class merge : public mu::script::operation
			{
			public:
				bool operator () (mu::script::context & context_a) override;
                static auto core (mu::core::errors::error_target & errors_a, mu::script::parser_scope::node * target, mu::string const & prefix, mu::script::parser_scope::node * source) -> bool;
			};
		}
	}
}

