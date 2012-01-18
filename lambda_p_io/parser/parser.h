#pragma once

#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>

#include <stack>
#include <vector>
#include <map>

namespace lambda_p
{
	namespace errors
	{
		class error_target;
	}
}
namespace lambda_p_io
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
			parser (boost::shared_ptr <lambda_p::errors::error_target> errors_a, boost::function <void (boost::shared_ptr <lambda_p_io::ast::expression>)> target_a);
			void operator () (lambda_p_io::tokens::token * token);
			void reset ();
			boost::shared_ptr <lambda_p::errors::error_target> errors;
			boost::function <void (boost::shared_ptr <lambda_p_io::ast::expression>)> target;
			std::stack <boost::shared_ptr <lambda_p_io::tokens::visitor>> state;
		};
	}
}