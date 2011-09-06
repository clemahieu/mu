#pragma once

#include <lambda_p/serialization/parser/state.h>
#include <lambda_p/serialization/parser/result_position.h>
#include <lambda_p/serialization/parser/result_reference.h>

#include <boost/shared_ptr.hpp>

#include <map>

namespace lambda_p
{
	namespace serialization
	{
		namespace parser
		{
			class statement : public state
			{
			public:
				statement (size_t statement_number_a, ::std::wstring statement_name_a, ::boost::shared_ptr < ::std::map < ::lambda_p::serialization::parser::result_reference, ::lambda_p::serialization::parser::result_position> > positions_a);
				~statement (void);
				state_id state_type ();
				::std::wstring statement_name;
				size_t statement_number;
				size_t argument_count;
				bool have_target;
				::boost::shared_ptr < ::std::map < ::lambda_p::serialization::parser::result_reference, ::lambda_p::serialization::parser::result_position> > positions;
			};
		}
	}
}

