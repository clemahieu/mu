#pragma once

#include <mu/script/operation.h>

#include <vector>

#include <gc_allocator.h>

namespace mu
{
    namespace core
    {
        class node;
    }
	namespace script
	{
		namespace closure
		{
			class single : public mu::script::operation
			{
			public:
				single (mu::core::node * operation_a);
				single (mu::vector <mu::core::node *> & closed_a, mu::core::node * operation_a);
				bool operator () (mu::script::context & context_a) override;
				mu::core::node * operation_m;
				mu::vector <mu::core::node *> closed;
			};
		}
	}
}
