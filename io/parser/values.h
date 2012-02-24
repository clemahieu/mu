#pragma once

#include <core/context.h>
#include <io/tokens/visitor.h>

#include <boost/function.hpp>

#include <vector>

namespace mu
{
	namespace io
	{
		namespace ast
		{
			class node;
			class expression;
		}
		namespace parser
		{
			class parser;
			class values : public mu::io::tokens::visitor
			{
			public:
				values (mu::io::parser::parser & parser_a, boost::function <void (boost::shared_ptr <mu::io::ast::node>)> target_a);
				void operator () (mu::io::tokens::divider * token) override;
				void operator () (mu::io::tokens::identifier * token) override;
				void operator () (mu::io::tokens::left_square * token) override;
				void operator () (mu::io::tokens::right_square * token) override;
				void operator () (mu::io::tokens::stream_end * token) override;
				void operator () (mu::io::tokens::parameters * token) override;
				void subexpression (boost::shared_ptr <mu::io::ast::node> node_a);
				std::vector <boost::shared_ptr <mu::io::ast::node>> values_m;
				mu::io::parser::parser & parser;
				mu::core::context first;
				boost::function <void (boost::shared_ptr <mu::io::ast::node>)> target;
			};
		}
	}
}
