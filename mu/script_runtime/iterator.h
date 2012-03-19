#pragma once

#include <vector>

#include <boost/shared_ptr.hpp>

namespace mu
{
	namespace core
	{
		class node;
	}
	namespace script_runtime
	{
		class iterator
		{
		public:
			iterator (std::vector <boost::shared_ptr <mu::core::node>> & stack_a, size_t position_a);
			mu::script_runtime::iterator operator ++ ();
			mu::script_runtime::iterator operator -- ();
			mu::script_runtime::iterator operator + (size_t offset);
			mu::script_runtime::iterator operator - (size_t offset);
			boost::shared_ptr <mu::core::node> operator * ();
			bool operator == (mu::script_runtime::iterator const & other);
			bool operator != (mu::script_runtime::iterator const & other);
			std::vector <boost::shared_ptr <mu::core::node>> & stack;
			size_t position;
		};
	}
}