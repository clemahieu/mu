#pragma once

#include <vector>

#include <boost/shared_ptr.hpp>

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
			iterator (std::vector <boost::shared_ptr <mu::core::node>> & stack_a, size_t position_a);
			mu::script::iterator operator ++ ();
			mu::script::iterator operator -- ();
			mu::script::iterator operator + (size_t offset);
			mu::script::iterator operator - (size_t offset);
			boost::shared_ptr <mu::core::node> & operator * ();
			bool operator == (mu::script::iterator const & other) const;
			bool operator != (mu::script::iterator const & other) const;
			std::vector <boost::shared_ptr <mu::core::node>> & stack;
			size_t position;
		};
	}
}