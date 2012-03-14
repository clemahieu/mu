#pragma once

#include <mu/io/debugging/context.h>

#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>

#include <stack>
#include <vector>
#include <map>

namespace mu
{
	namespace core
	{
		namespace errors
		{
			class error_target;
		}
	}
	namespace io
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
				parser (boost::shared_ptr <mu::core::errors::error_target> errors_a, boost::function <void (boost::shared_ptr <mu::io::ast::node>)> target_a);
				void operator () (mu::io::tokens::token * token, mu::io::debugging::context context_a);
				void reset ();
				mu::io::debugging::context context;
				boost::shared_ptr <mu::core::errors::error_target> errors;
				boost::function <void (boost::shared_ptr <mu::io::ast::node>)> target;
				std::stack <boost::shared_ptr <mu::io::tokens::visitor>> state;
			};
		}
	}
}