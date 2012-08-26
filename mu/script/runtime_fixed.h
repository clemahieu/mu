#pragma once

#include <mu/script/operation.h>

namespace mu
{
	namespace script
	{
		namespace runtime
		{
			class fixed : public mu::script::operation
			{
			public:
				fixed (mu::core::node * node_a);
				bool operator () (mu::script::context & context_a) override;
				mu::core::node * node;
			};
		}
	}
}