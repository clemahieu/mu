#pragma once

#include <boost/iostreams/stream.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/algorithm/string/replace.hpp>

#include <lambda_p/core/routine.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/binder/data.h>
#include <lambda_p/core/association.h>

#include <vector>

namespace lambda_p
{
	namespace serialization
	{
		template <typename stream_type>
		class simple
		{
		public:
			simple (stream_type & target_a)
				: target (target_a)
			{
			}
			~simple (void)
			{
			}
			void routine (lambda_p::core::routine const * routine_a)
			{
                std::map < size_t, lambda_p::core::position> argument_positions;
                std::map < lambda_p::core::statement const *, size_t> statement_positions;
                routine_a->placement (argument_positions, statement_positions);
				association (argument_positions, routine_a->surface);
                for (auto i = routine_a->statements.begin (); i != routine_a->statements.end (); ++i)
                {
                    target << " ";
                    statement (argument_positions, statement_positions, *i);
                    target << "\n";
                }
				target << ":;";
			}
			void statement (std::map <size_t, lambda_p::core::position> & argument_positions, std::map <lambda_p::core::statement const *, size_t> & statement_positions, lambda_p::core::statement const * statement_a)
			{
                target << "statement";
                target << statement_positions [statement_a];
				node (argument_positions, statement_a->target);
				target << " ";
				association (argument_positions, statement_a->association);
			}
			void association (std::map < size_t, lambda_p::core::position> & argument_positions, lambda_p::core::association const * association_a)
			{
				for (auto i = association_a->declarations.begin (); i != association_a->declarations.end (); ++i)
				{
					target << "\n ";
					node (argument_positions, *i);
				}
				target << " ; ";
				for (auto i = association_a->references.begin (); i != association_a->references.end (); ++i)
                {
                    target << "\n  ";
                    node (argument_positions, *i);
                }
				target << "\n ;";
			}
			void node (std::map <size_t, lambda_p::core::position> & argument_positions, size_t node_a)
			{
                lambda_p::core::position position (argument_positions [node_a]);
                target << "declaration";
                target << position.argument;
			}
			stream_type & target;
		};
	}
}
