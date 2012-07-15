#pragma once

#include <vector>

#include <boost/shared_ptr.hpp>

#include <gc_allocator.h>

namespace mu
{
	namespace core
	{
		class node;
	}
	namespace script
	{
		class iterator
		{
		public:
			iterator (std::vector <mu::core::node *, gc_allocator <mu::core::node *>> & stack_a, size_t position_a);
			mu::script::iterator operator ++ ();
			mu::script::iterator operator -- ();
			mu::script::iterator operator + (size_t offset);
			mu::script::iterator operator - (size_t offset);
			mu::core::node * & operator * ();
			bool operator == (mu::script::iterator const & other) const;
			bool operator != (mu::script::iterator const & other) const;
			std::vector <mu::core::node *, gc_allocator <mu::core::node *>> & stack;
			size_t position;
		};
	}
}