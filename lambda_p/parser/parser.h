#pragma once

#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>

#include <lambda_p/parser/state.h>
#include <lambda_p/tokens/token.h>

#include <stack>
#include <map>
#include <vector>

namespace lambda_p
{
	namespace binder
	{
		class node;
	}
	namespace core
	{
		class routine;
	}
	namespace parser
	{
		class parser
		{
		public:
			parser (boost::function <void (boost::shared_ptr <lambda_p::core::routine>)> target_a);
			parser (boost::function <void (boost::shared_ptr <lambda_p::core::routine>)> target_a, std::vector <std::pair <std::wstring, boost::shared_ptr <lambda_p::binder::node>>> & injected_parameters_a);
			parser (boost::function <void (boost::shared_ptr <lambda_p::core::routine>)> target_a, std::vector <std::pair <std::wstring, boost::shared_ptr <lambda_p::binder::node>>> & injected_parameters_a, std::vector <std::wstring> & injected_returns_a);
			void operator () (lambda_p::tokens::token * token);
			void reset ();
			bool error ();
			lambda_p::parser::state_id current_state ();
			void error_message (std::wstring & target);
		private:
			void parse_internal (lambda_p::tokens::token * token);
			void parse_error (lambda_p::tokens::token * token);
			void parse_begin (lambda_p::tokens::token * token);
			void parse_routine (lambda_p::tokens::token * token);
			void parse_routine_body (lambda_p::tokens::token * token);
			void parse_statement (lambda_p::tokens::token * token);
			void parse_reference (lambda_p::tokens::token * token);
			void parse_data (lambda_p::tokens::token * token);
			void parse_declaration (lambda_p::tokens::token * token);
            void parse_finished (lambda_p::tokens::token * token);
			void parse_association (lambda_p::tokens::token * token);
			std::wstring token_type_name (lambda_p::tokens::token * token);
			boost::function <void (boost::shared_ptr <lambda_p::core::routine>)> target;
			std::vector <std::pair <std::wstring, boost::shared_ptr <lambda_p::binder::node>>> injected_parameters;
			std::vector <std::wstring> injected_returns;
		public:
			boost::shared_ptr <lambda_p::parser::state> last_state;
			std::stack <boost::shared_ptr <lambda_p::parser::state>> state;
		};
	}
}