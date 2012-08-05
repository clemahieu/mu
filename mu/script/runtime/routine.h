#pragma once

#include <mu/script/operation.h>

#include <vector>

#include <gc_allocator.h>

namespace mu
{
	namespace script
	{
		namespace topology
		{
			class node;
		}
		namespace runtime
		{
			class expression;
			class routine : public mu::script::operation
			{
			public:
				routine ();
				bool operator () (mu::script::context & context_a) override;
				std::vector <mu::script::runtime::expression *, gc_allocator <mu::script::runtime::expression *>> expressions;
			};
		}
	}
}