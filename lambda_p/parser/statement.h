#pragma once

#include <lambda_p/parser/state.h>
#include <lambda_p/parser/result_position.h>
#include <lambda_p/parser/result_reference.h>

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
		class statement : public state
		{
		public:
			statement (::boost::shared_ptr < ::lambda_p::parser::body> body_a, ::std::wstring statement_name_a);
			~statement (void);
			state_id state_type ();
			::std::wstring statement_name;
			bool have_target;
			bool have_argument;
			::boost::shared_ptr < ::lambda_p::core::routine> & routine ();
			::boost::shared_ptr < ::lambda_p::parser::body> body;
			::lambda_p::core::statement * statement_m;
		};
	}
}

