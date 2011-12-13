#pragma once

#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>

#include <lambda_p/parser/state.h>

#include <stack>
#include <vector>
#include <map>

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
	namespace tokens
	{
		class token;
		class identifier;
	}
	namespace parser
	{
		class state;
		class association;
		class begin;
		class routine;
		class statement;
		class error;
		class state_factory;
		class parser
		{
		public:
			parser (boost::function <void (boost::shared_ptr <lambda_p::core::routine>)> target_a, std::map <std::wstring, boost::shared_ptr <lambda_p::parser::state_factory>> & keywords_a, std::vector <std::pair <std::wstring, boost::shared_ptr <lambda_p::binder::node>>> & injected_parameters_a, std::vector <std::wstring> & injected_returns_a);
			void operator () (lambda_p::tokens::token * token);
			void reset ();
			boost::shared_ptr <lambda_p::parser::error> error ();
			void process_token (lambda_p::tokens::token * token);
		private:
			boost::function <void (boost::shared_ptr <lambda_p::core::routine>)> target;
			std::vector <std::pair <std::wstring, boost::shared_ptr <lambda_p::binder::node>>> injected_parameters;
			std::vector <std::wstring> injected_returns;
			std::map <std::wstring, boost::shared_ptr <lambda_p::parser::state_factory>> keywords;
		public:
			boost::shared_ptr <lambda_p::parser::state> last_state;
			std::stack <boost::shared_ptr <lambda_p::parser::state>> state;
		};
	}
}