#pragma once

#include <lambda_p/parser/state.h>

namespace lambda_p
{
	namespace core
	{
		class routine;
	}
	namespace parser
	{
		class data_target;
		class data : public state
		{
		public:
			data (::boost::shared_ptr < ::lambda_p::core::routine> routine_a, ::boost::shared_ptr < ::lambda_p::parser::data_target> target_a);
			~data (void);
			state_id state_type ();
			::boost::shared_ptr < ::lambda_p::core::routine> routine;
			::boost::shared_ptr < ::lambda_p::parser::data_target> target;
		};
	}
}

