#pragma once

#include <lambda_p_serialization/parser/state.h>
#include <lambda_p_serialization/parser/routine_state.h>
#include <lambda_p_serialization/parser/expression_sink.h>
#include <lambda_p_serialization/parser/signature_sink.h>

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
		class routine : public lambda_p_serialization::parser::state, public lambda_p_serialization::parser::expression_sink, public lambda_p_serialization::parser::signature_sink
		{
		public:
			routine (lambda_p_serialization::parser::parser & parser_a, boost::function <void (boost::shared_ptr <lambda_p::core::routine> routine)> target_a);
			void parse (lambda_p_serialization::tokens::token * token) override;
			void reset ();
			void operator () (std::vector <std::wstring> parameters, std::wstring full_parameter) override;
			void operator () (boost::shared_ptr <lambda_p::core::expression> expression) override;
			void add_name (std::wstring name, boost::shared_ptr <lambda_p::core::scatter> scatter_a, size_t position);
			lambda_p_serialization::parser::parser & parser;
			lambda_p_serialization::parser::routine_state::routine_state state;
			boost::shared_ptr <lambda_p::core::routine> routine_m;
			std::multimap <std::wstring, std::pair <boost::shared_ptr <lambda_p_serialization::parser::expression>, size_t>> unresolved_references;
			std::map <std::wstring, boost::shared_ptr <lambda_p_serialization::parser::reference>> names;
			boost::function <void (boost::shared_ptr <lambda_p::core::routine> routine)> target;
		};
	}
}

