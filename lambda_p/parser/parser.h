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
	}
	namespace parser
	{
		class state;
		class association;
		class begin;
		class routine;
		class statement;
		class error;
		class data;
		class state_factory;
		class parser
		{
			friend class lambda_p::parser::association;
			friend class lambda_p::parser::begin;
			friend class lambda_p::parser::routine;
			friend class lambda_p::parser::statement;
			friend class lambda_p::parser::data;
		public:
			parser (boost::function <void (boost::shared_ptr <lambda_p::core::routine>)> target_a);
			parser (boost::function <void (boost::shared_ptr <lambda_p::core::routine>)> target_a, std::vector <std::pair <std::wstring, boost::shared_ptr <lambda_p::binder::node>>> & injected_parameters_a);
			parser (boost::function <void (boost::shared_ptr <lambda_p::core::routine>)> target_a, std::vector <std::pair <std::wstring, boost::shared_ptr <lambda_p::binder::node>>> & injected_parameters_a, std::vector <std::wstring> & injected_returns_a);
			void operator () (lambda_p::tokens::token * token);
			void reset ();
			boost::shared_ptr <lambda_p::parser::error> error ();
		private:
			std::wstring token_type_name (lambda_p::tokens::token * token);
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