#pragma once

#include <lambda_p/parser/state.h>
#include <lambda_p/parser/routine.h>
#include <lambda_p/parser/association_target.h>

#include <boost/shared_ptr.hpp>

#include <map>

namespace lambda_p
{
	namespace core
	{
		class statement;
		class routine;
	}
	namespace parser
	{
		class body;
		class statement : public state, public ::lambda_p::parser::association_target
		{
		public:
			statement (::boost::shared_ptr < ::lambda_p::parser::routine> routine_a);
			~statement (void);
			state_id state_type ();
			void sink_result (size_t * & declaration);
			void sink_argument (size_t * & argument);
			bool have_target;
			bool on_results;
			::boost::shared_ptr < ::lambda_p::parser::routine> routine;
			::lambda_p::core::statement * statement_m;
		};
	}
}

