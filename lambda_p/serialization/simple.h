#pragma once

#include <boost/iostreams/stream.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/algorithm/string/replace.hpp>

#include <lambda_p/core/routine.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/core/node.h>
#include <lambda_p/core/data.h>

namespace lambda_p
{
	namespace serialization
	{
		template <class stream_type>
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
			void routine (::lambda_p::core::routine const * routine_a)
			{
				node (&routine_a->declaration);
				target << "\n";
				for (::std::vector < ::lambda_p::core::node *>::const_iterator i = routine_a->parameters.begin (); i != routine_a->parameters.end (); ++i)
				{
					target << " ";
					node (*i);
					target << "\n";
				}
				target << ";;\n";
				for (::std::vector < ::lambda_p::core::statement>::const_iterator i = routine_a->body.begin (); i != routine_a->body.end (); ++i)
				{
					statement (&(*i));
				}
				target << ";.\n\n";
			}
			void statement (::lambda_p::core::statement const * statement_a)
			{
				target << "  ";
				node (statement_a->declaration);
				target << "\n";
				target << "  ";
				node (statement_a->target);
				target << "\n";
				for (::std::vector < ::lambda_p::core::node *>::const_iterator i = statement_a->arguments.begin (); i != statement_a->arguments.end (); ++i)
				{
					target << "  ";
					node (*i);
					target << " ";
				}
				target << ";;\n";
			}
			void node (::lambda_p::core::node const * node_a)
			{
				target << node_a;
			}
			void data (::lambda_p::core::data const * data_a)
			{
				target << data_a->item;
			}
			stream_type & target;
		};
	}
}
