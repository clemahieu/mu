#pragma once

#include <mu/script/operation.h>

namespace mu
{
	namespace script
	{
		namespace string
		{
			class node;
		}
		namespace cluster
		{
			class node;
		}
		namespace loads
		{
			class operation : public mu::script::operation
			{
			public:
				bool operator () (mu::script::context & context_a) override;
				mu::script::cluster::node * core (mu::script::context & context_a, mu::script::string::node * file);
			};
		}
	}
}

