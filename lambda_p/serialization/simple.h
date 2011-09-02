#pragma once

#include <boost/iostreams/stream.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/algorithm/string/replace.hpp>

#include <lambda_p/core/routine.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/core/node.h>
#include <lambda_p/core/data.h>
#include <lambda_p/core/parameter_ref.h>
#include <lambda_p/core/result_ref.h>
#include <lambda_p/core/result.h>

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
                target << "routine";
                target << routine_a;
                target << "\n";
                for (size_t i = 0; i != routine_a->parameters; ++i)
                {
                    target << " ";
                    target << "parameter";
                    target << i;
                    target << "\n";
                }
                target << ";,\n";
                for (::std::vector < ::lambda_p::core::statement *>::const_iterator i = routine_a->statements.begin (); i != routine_a->statements.end (); ++i)
                {
                    target << " ";
                    statement (*i);
                    target << "\n";
                }
                target << ";;";
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
                target << "\n ;,";
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
                    ::lambda_p::core::result_ref const * result_ref_l = dynamic_cast < ::lambda_p::core::result_ref const *> (node_a);
                    if (result_ref_l != NULL)
                    {
                        result_ref (result_ref_l);
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
                            ::lambda_p::core::result const * result_l = dynamic_cast < ::lambda_p::core::result const *> (node_a);
                            if (result_l != NULL)
                            {
                                result (result_l);
                            }
                            else
                            {
                                assert (false);
                            }
                        }
                    }
                }
			}
			void data (::lambda_p::core::data const * data_a)
			{
                target << ";' ";
                target << data_a->item ().get ();
			}
            void parameter_ref (::lambda_p::core::parameter_ref const * parameter_ref_a)
            {
                target << "routine";
                target << parameter_ref_a->routine;
                target << " ;. ";
                target << "parameter";
                target << parameter_ref_a->target_parameter;
            }
            void result_ref (::lambda_p::core::result_ref const * result_ref_a)
            {
                target << "statement";
                target << result_ref_a->target_statement;
                target << " ;. ";
                target << "result";
                target << result_ref_a->target_argument;
            }
			void result (::lambda_p::core::result const * result_a)
			{
				target << ";! ";
                target << "result";
                target << result_a->self_argument;
			}
			stream_type & target;
		};
	}
}
