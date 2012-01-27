#pragma once

#include <lambda_p/context.h>

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
	}
	namespace parser
	{
		class begin;
		class error;
		class parser
		{
		public:
			parser (boost::shared_ptr <lambda_p::errors::error_target> errors_a, boost::function <void (boost::shared_ptr <lambda_p_io::ast::node>)> target_a);
			void operator () (lambda_p_io::tokens::token * token, lambda_p::context context_a);
			void reset ();
			lambda_p::context context;
			boost::shared_ptr <lambda_p::errors::error_target> errors;
			boost::function <void (boost::shared_ptr <lambda_p_io::ast::node>)> target;
			std::stack <boost::shared_ptr <lambda_p_io::tokens::visitor>> state;
		};
	}
}