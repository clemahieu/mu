#pragma once

#include <boost/shared_ptr.hpp>

#include <lambda_p/serialization/parser/state.h>
#include <lambda_p/core/routine.h>
#include <lambda_p/serialization/parser/result_position.h>
#include <lambda_p/serialization/parser/result_reference.h>

#include <map>

namespace lambda_p
{
	namespace serialization
	{
		namespace parser
		{
			class routine_parameter : public state
			{
			public:
				routine_parameter(::std::wstring routine_name_a);
				~routine_parameter(void);
				state_id state_type ();
				::std::wstring routine_name;	
				size_t parameter_count;
				::boost::shared_ptr < ::std::map < ::lambda_p::serialization::parser::result_reference, ::lambda_p::serialization::parser::result_position> > positions;
			};
		}
	}
}
