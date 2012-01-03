#pragma once

#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>

#include <stack>
#include <vector>
#include <map>

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
		class expression;
	}
	namespace parser
	{
		class begin;
		class error;
		class parser
		{
		public:
			parser (boost::function <void (boost::shared_ptr <lambda_p_serialization::ast::expression>)> target_a);
			void operator () (lambda_p_serialization::tokens::token * token);
			void reset ();
			boost::shared_ptr <lambda_p_serialization::parser::error> error ();
		private:
			boost::function <void (boost::shared_ptr <lambda_p_serialization::ast::expression>)> target;
		public:
			std::stack <boost::shared_ptr <lambda_p_serialization::tokens::visitor>> state;
		};
	}
}