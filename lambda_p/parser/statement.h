#pragma once

#include <lambda_p/parser/state.h>
#include <lambda_p/parser/reference_identifiers.h>

#include <boost/shared_ptr.hpp>

#include <map>

namespace lambda_p
{
	namespace core
	{
		class statement;
		class routine;
		class reference;
	}
	namespace parser
	{
		class body;
		class statement : public state
		{
		public:
			statement (::boost::shared_ptr < ::lambda_p::parser::routine> routine_a);
			~statement (void);
			state_id state_type ();
			bool have_target;
			bool on_results;
			::boost::shared_ptr < ::lambda_p::parser::routine> routine;
			::lambda_p::core::statement * statement_m;
		};
	}
}

