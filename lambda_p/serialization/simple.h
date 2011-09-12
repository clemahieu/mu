#pragma once

#include <boost/iostreams/stream.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/algorithm/string/replace.hpp>

#include <lambda_p/core/routine.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/core/node.h>
#include <lambda_p/core/data.h>
#include <lambda_p/core/reference.h>
#include <lambda_p/core/declaration.h>

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
			void routine (::lambda_p::core::routine const * routine_a)
			{
                for (::std::vector < ::lambda_p::core::statement *>::const_iterator i = routine_a->statements.begin (); i != routine_a->statements.end (); ++i)
                {
                    target << " ";
                    statement (*i);
                    target << "\n";
                }
                target << ";.";
			}
			void statement (::lambda_p::core::statement const * statement_a)
			{
                target << "statement";
                target << statement_a->index;
                for (::std::vector < ::lambda_p::core::node *>::const_iterator i = statement_a->arguments.begin (); i != statement_a->arguments.end (); ++i)
                {
                    target << "\n  ";
                    node (*i);
                }
                target << "\n ;;";
			}
			void node (::lambda_p::core::node const * node_a)
			{
				::lambda_p::core::node_id node_id (node_a->node_type ());
				switch (node_id)
				{
				case ::lambda_p::core::node_reference:
					result_ref (static_cast < ::lambda_p::core::reference const *> (node_a));
					break;
				case ::lambda_p::core::node_data:
					data (static_cast < ::lambda_p::core::data const *> (node_a));
					break;
				case ::lambda_p::core::node_declaration:
					result (static_cast < ::lambda_p::core::declaration const *> (node_a));
					break;
				default:
					assert (false);
					break;
				}
			}
			void data (::lambda_p::core::data const * data_a)
			{
                target << ";' ";
                target << data_a->item ().get ();
			}
            void result_ref (::lambda_p::core::reference const * result_ref_a)
            {
                target << "statement";
                target << result_ref_a->target_statement;
                target << " ";
                target << "declaration";
                target << result_ref_a->target_argument;
            }
			void result (::lambda_p::core::declaration const * result_a)
			{
				target << ";! ";
                target << "declaration";
                target << result_a->self_argument;
			}
			stream_type & target;
		};
	}
}
