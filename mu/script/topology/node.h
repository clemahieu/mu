#pragma once

#include <mu/core/node.h>

#include <vector>

#include <gc_allocator.h>

namespace mu
{
	namespace core
	{
		class expression;
	}
	namespace script
	{
		namespace topology
		{
			class node : public mu::core::node
			{
			public:				
				std::vector <mu::core::expression *, gc_allocator <mu::core::expression *>> expressions;
			};
		}
	}
}