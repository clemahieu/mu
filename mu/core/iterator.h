#pragma once

#include <vector>

#include <gc_allocator.h>

namespace mu
{
	namespace core
	{
		class node;
		class iterator
		{
		public:
			iterator (std::vector <mu::core::node *, gc_allocator <mu::core::node *>> & stack_a, size_t position_a);
			mu::core::iterator operator ++ ();
			mu::core::iterator operator -- ();
			mu::core::iterator operator + (size_t offset);
			mu::core::iterator operator - (size_t offset);
			mu::core::node * & operator * ();
			bool operator == (mu::core::iterator const & other) const;
			bool operator != (mu::core::iterator const & other) const;
			std::vector <mu::core::node *, gc_allocator <mu::core::node *>> & stack;
			size_t position;
		};
	}
}