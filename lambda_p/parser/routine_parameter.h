#pragma once

#include <boost/shared_ptr.hpp>

#include <lambda_p/parser/state.h>
#include <lambda_p/core/routine.h>
#include <lambda_p/parser/result_position.h>
#include <lambda_p/parser/result_reference.h>

#include <map>

namespace lambda_p
{
	namespace parser
	{
		class routine;
		class routine_parameter : public state
		{
		public:
			routine_parameter (::boost::shared_ptr < ::lambda_p::parser::routine> routine_a, ::std::wstring routine_name_a);
			~routine_parameter (void);
			state_id state_type ();
			::std::wstring routine_name;
			::boost::shared_ptr < ::lambda_p::parser::routine> routine;
			::std::map < ::std::wstring, size_t> positions;
		};
	}
}
