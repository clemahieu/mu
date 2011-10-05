#pragma once

#include <boost/shared_ptr.hpp>

#include <lambda_p/parser/state.h>
#include <lambda_p/parser/association_target.h>

#include <map>

namespace lambda_p
{
	namespace binder 
	{
		class node_instance;
	}
	namespace core
	{
		class routine;
		class declaration;
	}
	namespace parser
	{
		class routine : public state, public ::lambda_p::parser::association_target
		{
		public:
			routine(void);
			~routine(void);
			state_id state_type ();
			void sink_result (::lambda_p::core::declaration * declaration);
			void sink_argument (::lambda_p::core::node * argument);
			::boost::shared_ptr < ::lambda_p::core::routine> routine_m;
			bool have_surface;
			::std::multimap < ::std::wstring, ::lambda_p::core::declaration *> unresolved_references;
			::std::map < ::std::wstring, ::lambda_p::core::declaration *> positions;
			bool parsed_routine;
		};
	}
}

