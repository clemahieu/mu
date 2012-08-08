#pragma once

#include <mu/core/iterator.h>

#include <vector>

namespace mu
{
	namespace core
	{
		class node;
        namespace errors
        {
            class error_target;
        }
		class context
		{
		public:
			context ();
			context (mu::core::errors::error_target & errors_a);
			mu::core::node * & parameters (size_t offset);
			size_t parameters_size ();
			mu::core::iterator parameters_begin ();
			mu::core::iterator parameters_end ();
			mu::core::node * & locals (size_t offset);
			size_t locals_size ();
			mu::core::iterator locals_begin ();
			mu::core::iterator locals_end ();
			mu::core::node * & working (size_t offset);
			size_t working_size ();
			mu::core::iterator working_begin ();
			mu::core::iterator working_end ();
			void drop ();
			void slide ();
			void push (mu::core::node * node_a);
			void reserve (size_t count_a);
			template <typename G> void push (G begin_a, G end_a)
			{
				for (auto current (begin_a); current != end_a; ++current)
				{
					push (*current);
				}
			}
			template <typename G, typename H> void assign (H target_a, G begin_a, G end_a)
			{
				auto target_l (target_a);
				for (auto current (begin_a); current != end_a; ++current, ++target_l)
				{
					*target_l = *current;
				}
			}
			std::vector <mu::core::node *, gc_allocator <mu::core::node *>> stack;
			size_t base_begin;
			size_t base_end;
			size_t frame_begin;
			mu::core::errors::error_target & errors;
		};
	}
}