#pragma once

#include <boost/iostreams/stream.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/algorithm/string/replace.hpp>

#include <lambda_p/core/routine.h>
#include <lambda_p/core/body.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/core/node.h>

namespace lambda_p
{
	namespace serialization
	{
		template <class stream_type>
		class simple
		{
		public:
			simple (::boost::shared_ptr < stream_type> target_a)
				: target (target_a)
			{
			}
			~simple (void)
			{
			}
			void routine (::boost::shared_ptr < ::lambda_p::core::routine> routine_a)
			{
				*target << routine_a->name;
				*target << "\n";
				for (::std::vector < ::boost::shared_ptr < ::lambda_p::core::node> >::iterator i = routine_a->surface.begin (); i != routine_a->surface.end (); ++i)
				{
					*target << " ";
					node (*i);
					*target << "\n";
				}
				*target << ".\n";
				body (routine_a->body);
				*target << ".\n";
			}
			void body (::boost::shared_ptr < ::lambda_p::core::body> body_a)
			{
				for (::std::vector < ::boost::shared_ptr < ::lambda_p::core::statement> >::iterator i = body_a->statements.begin (); i != body_a->statements.end (); ++i)
				{
					statement (*i);
				}
			}
			void statement (::boost::shared_ptr < ::lambda_p::core::statement> statement_a)
			{
				*target << " ";
				node (statement_a->target);
				*target << "\n";
				for (::std::vector < ::boost::shared_ptr < ::lambda_p::core::node> >::iterator i = statement_a->connections.begin (); i != statement_a->connections.end (); ++i)
				{
					*target << "  ";
					node (*i);
					*target << "\n";
				}
				*target << " .\n";
			}
			void node (::boost::shared_ptr < ::lambda_p::core::node> node_a)
			{
				::std::string escaped = ::boost::algorithm::replace_all_copy (node_a->name, ".", ".\\");
				*target << escaped;
			}
			::boost::shared_ptr < stream_type> target;
		};
	}
}
