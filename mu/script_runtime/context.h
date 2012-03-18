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
		class context
		{
		public:
			context ();
			boost::shared_ptr <mu::core::node> parameters (size_t offset);
			size_t parameters_size ();
			boost::shared_ptr <mu::core::node> locals (size_t offset);
			size_t locals_size ();
			boost::shared_ptr <mu::core::node> working (size_t offset);
			size_t working_size ();
			void enter ();
			void leave ();
			void drop ();
			void slide ();
			void push (boost::shared_ptr <mu::core::node> node_a);
			bool operator () ();
			std::vector <boost::shared_ptr <mu::core::node>> stack;
			size_t base_begin;
			size_t base_end;
			size_t working_begin;
		};
	}
}