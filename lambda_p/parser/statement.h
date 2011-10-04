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
			statement (::boost::shared_ptr < ::lambda_p::core::routine> body_a, ::std::wstring statement_name_a);
			~statement (void);
			state_id state_type ();
			::std::wstring statement_name;
			bool have_target;
			bool on_lhs;
			void sink_reference (::lambda_p::parser::simple_parser & parser, ::lambda_p::parser::reference_identifiers reference);
			void sink_data (::lambda_p::parser::simple_parser & parser, ::lambda_p::tokens::identifier * identifier);
			::boost::shared_ptr < ::lambda_p::core::routine> routine ();
			::lambda_p::core::statement * statement_m;
		};
	}
}

