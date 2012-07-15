#pragma once

#include <mu/script/operation.h>

#include <boost/shared_ptr.hpp>

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
				single (std::vector <mu::core::node *, gc_allocator <mu::core::node *>> & closed_a, mu::core::node * operation_a);
				bool operator () (mu::script::context & context_a) override;
				std::wstring name () override;
				mu::core::node * operation_m;
				std::vector <mu::core::node *, gc_allocator <mu::core::node *>> closed;
			};
		}
	}
}
