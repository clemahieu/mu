#pragma once

#include <lambda_p/parser/state.h>
#include <lambda_p/parser/routine_parameter.h>
#include <lambda_p/parser/reference_identifiers.h>
#include <lambda_p/parser/reference_position.h>

#include <boost/scoped_ptr.hpp>

#include <map>

namespace lambda_p
{
	namespace core
	{
		class routine;
		class reference;
	}
	namespace parser
	{
		class routine;
		class body : public state
		{
		public:
			body (::boost::shared_ptr < ::lambda_p::parser::routine> routine_a, ::std::wstring routine_name_a, ::std::map < ::std::wstring, size_t> parameter_positions_a);
			~body (void);
			state_id state_type ();
			::boost::shared_ptr < ::lambda_p::core::routine> & routine ();
			::std::wstring routine_name;
			::boost::shared_ptr < ::lambda_p::parser::routine> routine_m;
			::std::multimap < ::lambda_p::parser::reference_identifiers, ::lambda_p::core::reference *> unresolved_references;
			::std::map < ::std::wstring, size_t> parameter_positions;
			::std::map < ::lambda_p::parser::reference_identifiers, ::lambda_p::parser::reference_position> positions;
		};
	}
}
