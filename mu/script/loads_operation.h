#pragma once

#include <mu/script/operation.h>

namespace mu
{
    namespace io
    {
        namespace keywording
        {
            class extensions;
        }
    }
	namespace script
	{
		namespace file
		{
			class node;
		}
		namespace cluster
		{
			class node;
		}
        namespace parser_scope
        {
            class node;
        }
		namespace loads
		{
			class operation : public mu::script::operation
			{
			public:
				bool operator () (mu::script::context & context_a) override;
				static auto core (mu::script::context & context_a, mu::script::parser_scope::node * scope_a, mu::script::file::node * file) -> mu::script::cluster::node *;
			};
		}
        namespace loads_extensions
        {
            class operation : public mu::script::operation
            {
            public:
				bool operator () (mu::script::context & context_a) override;
            };
        }
	}
}

