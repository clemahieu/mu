#pragma once

#include <mu/io/debugging/context.h>
#include <mu/io/parser/target.h>

#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>

#include <stack>
#include <vector>
#include <map>
#include <deque>

#include <gc_allocator.h>

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
			class cluster;
		}
		namespace parser
		{
			class begin;
			class error;
			class parser : public mu::io::parser::target
			{
			public:
				parser (mu::core::errors::error_target * errors_a, boost::function <void (mu::io::ast::cluster *)> target_a);
				void operator () (mu::io::tokens::token * token, mu::io::debugging::context context_a);
				void operator () (mu::io::ast::expression * expression_a) override;
				void reset ();
				void finish ();
				mu::io::debugging::context context;
				mu::io::ast::cluster * cluster;
				mu::core::errors::error_target * errors;
				boost::function <void (mu::io::ast::cluster *)> target;
				std::stack <mu::io::tokens::visitor *, std::deque <mu::io::tokens::visitor *, gc_allocator <mu::io::tokens::visitor *>>> state;
			};
		}
	}
}