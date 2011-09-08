#pragma once

#include <lambda_p/serialization/parser/state.h>
#include <lambda_p/serialization/parser/result_position.h>
#include <lambda_p/serialization/parser/result_reference.h>

#include <boost/shared_ptr.hpp>

#include <map>

namespace lambda_p
{
	namespace core
	{
		class statement;
		class routine;
	}
	namespace serialization
	{
		namespace parser
		{
			class body;
			class statement : public state
			{
			public:
				statement (::lambda_p::serialization::parser::body * body_a, ::std::wstring statement_name_a);
				~statement (void);
				state_id state_type ();
				::std::wstring statement_name;
				bool have_target;
				::boost::shared_ptr < ::lambda_p::core::routine> & routine ();
				::lambda_p::serialization::parser::body * body;
				::lambda_p::core::statement * statement_m;
			};
		}
	}
}

