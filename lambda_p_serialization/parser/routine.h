#pragma once

#include <lambda_p_serialization/parser/state.h>
#include <lambda_p_serialization/parser/routine_state.h>

#include <map>
#include <string>
#include <vector>

#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>

namespace lambda_p
{
	namespace core
	{
		class routine;
		class expression;
		class scatter;
		class target;
		class tee;
	}
}
namespace lambda_p_serialization
{
	namespace tokens
	{
		class identifier;
	}
	namespace parser
	{
		class parser;
		class expression;
		class reference;
		class routine : public lambda_p_serialization::parser::state
		{
		public:
			routine (lambda_p_serialization::parser::parser & parser_a, boost::function <void (boost::shared_ptr <lambda_p::core::routine> routine)> target_a);
			void parse (lambda_p_serialization::tokens::token * token) override;
			void reset ();
			void add_name (std::wstring name, boost::shared_ptr <lambda_p_serialization::parser::reference> reference);
			lambda_p_serialization::parser::parser & parser;
			lambda_p_serialization::parser::routine_state::routine_state state;
			boost::shared_ptr <lambda_p::core::tee> tee;
			boost::shared_ptr <lambda_p::core::routine> routine_m;
			std::multimap <std::wstring, boost::shared_ptr <lambda_p::core::target>> unresolved_references;
			std::map <std::wstring, boost::shared_ptr <lambda_p_serialization::parser::reference>> names;
			boost::function <void (boost::shared_ptr <lambda_p::core::routine> routine)> target;
		};
	}
}

