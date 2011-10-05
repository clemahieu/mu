#pragma once

#include <lambda_p/parser/state.h>
#include <lambda_p/parser/data_target.h>

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	namespace parser
	{
		class routine;
		class association_target;
		class association : public ::lambda_p::parser::state, public data_target
		{
		public:
			association (::boost::shared_ptr < ::lambda_p::parser::routine> routine_a, ::boost::shared_ptr < ::lambda_p::parser::association_target> target_a);
			state_id state_type ();
			void sink_data (::lambda_p::core::node * data);
			bool on_results;
			::boost::shared_ptr < ::lambda_p::parser::routine> routine;
			::boost::shared_ptr < ::lambda_p::parser::association_target> target;
		private:
		};
	}
}

