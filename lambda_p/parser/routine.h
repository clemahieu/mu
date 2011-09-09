#pragma once

#include <boost/shared_ptr.hpp>

#include <lambda_p/parser/state.h>

namespace lambda_p
{
	namespace core
	{
		class routine;
	}
	namespace parser
	{
		class routine : public state
		{
		public:
			routine(void);
			~routine(void);
			state_id state_type ();
			::boost::shared_ptr < ::lambda_p::core::routine> routine_m;
			bool parsed_routine;
		};
	}
}

