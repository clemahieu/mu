#pragma once

#include <boost/iostreams/stream.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/algorithm/string/replace.hpp>

#include <lambda_p/core/routine.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/core/node.h>
#include <lambda_p/core/data.h>
#include <lambda_p/core/parameter_ref.h>
#include <lambda_p/core/results_ref.h>

#include <vector>

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
                
			}
			void statement (::lambda_p::core::statement const * statement_a)
			{
                for (::std::vector < ::lambda_p::core::node *>::const_iterator i = statement_a->statement.begin (); i != statement_a->statement.end (); ++i)
                {
                    target << " ":
                    statement (*i);
                }
			}
			void node (::lambda_p::core::node const * node_a)
			{
                ::lambda_p::core::parameter_ref const * parameter_ref_l = dynamic_cast < ::lambda_p::core::parameter_ref const *> (node_a);
                if (parameter_ref_l != NULL)
                {
                    parameter_ref (parameter_ref_l);
                }
                else
                {
                    ::lambda_p::core::results_ref const * results_ref_l = dynamic_cast < ::lambda_p::core::results_ref const *> (node_a);
                    if (results_ref_l != NULL)
                    {
                        results_ref (results_ref_l);
                    }
                    else
                    {
                        ::lambda_p::core::data const * data_l = dynamic_cast < ::lambda_p::core::data const *> (node_a);
                        if (data_l != NULL)
                        {
                            data (data_l);
                        }
                        else
                        {
                            assert (false);
                        }
                    }
                }
			}
			void data (::lambda_p::core::data const * data_a)
			{
				target << data_a->item;
			}
            void parameter_ref (::lambda_p::core::parameter_ref const * parameter_ref_a)
            {
                target << &parameter_ref_a->routine;
                target << " ";
                target << parameter_ref_a->index;
            }
            void results_ref (::lambda_p::core::results_ref const * results_ref_a)
            {
                target << result_ref_a->statement;
                target << " ";
                target << result_ref_a->index;
            }
			stream_type & target;
		};
	}
}
