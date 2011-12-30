#pragma once

#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>

#include <stack>
#include <vector>
#include <map>

namespace lambda_p
{
	namespace core
	{
		class routine;
		class node;
	}
}
namespace lambda_p_serialization
{
	namespace tokens
	{
		class token;
		class identifier;
		class visitor;
	}
	namespace ast
	{
		class node;
	}
	namespace parser
	{
		class state;
		class begin;
		class routine;
		class error;
		class state_factory;
		class reference;
		class parser
		{
			friend class lambda_p_serialization::parser::routine;
		public:
			parser (boost::function <void (boost::shared_ptr <lambda_p::core::routine>)> target_a, std::map <std::wstring, boost::shared_ptr <lambda_p_serialization::parser::state_factory>> & keywords_a, std::map <std::wstring, boost::shared_ptr <lambda_p_serialization::parser::reference>> & globals_a);
			void operator () (lambda_p_serialization::tokens::token * token);
			void reset ();
			boost::shared_ptr <lambda_p_serialization::parser::error> error ();
		private:
			void process_token (lambda_p_serialization::tokens::token * token);
			boost::function <void (boost::shared_ptr <lambda_p_serialization::ast::node>)> target;
			std::map <std::wstring, boost::shared_ptr <lambda_p_serialization::parser::reference>> globals;
			std::map <std::wstring, boost::shared_ptr <lambda_p_serialization::parser::state_factory>> keywords;
		public:
			std::stack <boost::shared_ptr <lambda_p_serialization::tokens::visitor>> state;
		};
	}
}