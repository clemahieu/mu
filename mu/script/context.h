#pragma once

#include <mu/script/iterator.h>
#include <mu/core/errors/errors.h>

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
		class context
		{
		public:
			context ();
			context (mu::core::errors::errors errors_a);
			boost::shared_ptr <mu::core::node> parameters (size_t offset);
			size_t parameters_size ();
			mu::script::iterator parameters_begin ();
			mu::script::iterator parameters_end ();
			boost::shared_ptr <mu::core::node> locals (size_t offset);
			size_t locals_size ();
			mu::script::iterator locals_begin ();
			mu::script::iterator locals_end ();
			boost::shared_ptr <mu::core::node> working (size_t offset);
			size_t working_size ();
			mu::script::iterator working_begin ();
			mu::script::iterator working_end ();
			void enter ();
			void leave ();
			void drop ();
			void slide ();
			void push (boost::shared_ptr <mu::core::node> node_a);
			void push (mu::script::iterator & begin_a, mu::script::iterator & end_a);
			bool operator () ();
			std::vector <boost::shared_ptr <mu::core::node>> stack;
			size_t base_begin;
			size_t base_end;
			size_t frame_begin;
			mu::core::errors::errors errors;
		};
	}
}