#pragma once

#include <mu/script/operation.h>

namespace mu
{
	namespace core
	{
		class cluster;
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
		namespace extensions
		{
			class node;
		}
		namespace loads
		{
			class operation : public mu::script::operation
			{
			public:
				bool operator () (mu::script::context & context_a) override;
				mu::script::extensions::node * core (mu::script::context & context_a, mu::script::string::node * file);
			};
		}
	}
}

