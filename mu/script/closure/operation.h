#pragma once

#include <mu/script/operation.h>

#include <boost/shared_ptr.hpp>

#include <vector>

#include <gc_allocator.h>

namespace mu
{
	namespace script
	{
		namespace closure
		{
			class operation : public mu::script::operation
			{
			public:
				operation (size_t count_a, mu::script::operation * operation_a);
				operation (mu::script::operation * operation_a, std::vector <size_t> & open_a, std::vector <mu::core::node *, gc_allocator <mu::core::node *>> & closed_a);
				bool operator () (mu::script::context & context_a) override;
				std::wstring name () override;
				mu::script::operation * operation_m;
				std::vector <size_t> open;
				std::vector <mu::core::node *, gc_allocator <mu::core::node *>> closed;
			};
		}
	}
}
