#pragma once

#include <lambda_p/serialization/parser/state.h>
#include <lambda_p/serialization/parser/routine_parameter.h>

#include <boost/scoped_ptr.hpp>

#include <map>

namespace lambda_p
{
	namespace core
	{
		class routine;
	}
	namespace serialization
	{
		namespace parser
		{
			class body : public state
			{
			public:
				body (::boost::shared_ptr < ::lambda_p::core::routine> routine_a, ::std::wstring routine_name_a, ::std::map < ::std::wstring, size_t> parameter_positions_a);
				~body (void);
				state_id state_type ();
				::boost::shared_ptr < ::lambda_p::core::routine> routine;
				::std::wstring routine_name;
				::std::multimap < ::lambda_p::serialization::parser::result_reference, ::lambda_p::core::reference *> unresolved_references;
				::std::map < ::std::wstring, size_t> parameter_positions;
				::std::map < ::lambda_p::serialization::parser::result_reference, ::lambda_p::serialization::parser::result_position> positions;
			};
		}
	}
}
