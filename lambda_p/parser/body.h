#pragma once

#include <lambda_p/parser/state.h>
#include <lambda_p/parser/reference_identifiers.h>

#include <boost/scoped_ptr.hpp>

#include <map>

namespace lambda_p
{
	namespace core
	{
		class routine;
		class reference;
        class declaration;
	}
	namespace parser
	{
		class routine;
		class body : public state
		{
		public:
			body (::boost::shared_ptr < ::lambda_p::parser::routine> routine_a);
			~body (void);
			state_id state_type ();
			::boost::shared_ptr < ::lambda_p::core::routine> & routine ();
			::boost::shared_ptr < ::lambda_p::parser::routine> routine_m;
			::std::multimap < ::lambda_p::parser::reference_identifiers, ::lambda_p::core::reference *> unresolved_references;
			::std::map < ::lambda_p::parser::reference_identifiers, ::lambda_p::core::declaration *> positions;
		};
	}
}
