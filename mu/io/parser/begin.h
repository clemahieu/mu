#pragma once

#include <mu/io/tokens/visitor.h>

#include <boost/function.hpp>

namespace mu
{
	namespace io
	{	
		namespace ast
		{
			class node;
		}
		namespace parser
		{
			class parser;
			class begin : public mu::io::tokens::visitor
			{
			public:
				begin (mu::io::parser::parser & parser_a, boost::function <void (boost::shared_ptr <mu::io::ast::node>)> target_a);
				void operator () (mu::io::tokens::divider * token) override;
				void operator () (mu::io::tokens::identifier * token) override;
				void operator () (mu::io::tokens::left_square * token) override;
				void operator () (mu::io::tokens::right_square * token) override;
				void operator () (mu::io::tokens::stream_end * token) override;
				void operator () (mu::io::tokens::parameters * token) override;
				void unexpected_token (mu::io::tokens::token * token);
				mu::io::parser::parser & parser;
				boost::function <void (boost::shared_ptr <mu::io::ast::node>)> target;
			};
		}
	}
}

