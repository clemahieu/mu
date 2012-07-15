#pragma once

#include <mu/core/segment.h>

#include <boost/shared_ptr.hpp>

#include <gc_allocator.h>

namespace mu
{
	namespace core
	{
		class node;
		namespace apply
		{
			void merge (std::vector <mu::core::node *, gc_allocator <mu::core::node *>> & target, std::vector <mu::core::node *, gc_allocator <mu::core::node *>> & source);
		}
	}
}
