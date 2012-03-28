#pragma once

#include <mu/io/debugging/context.h>
#include <mu/io/tokens/visitor.h>
#include <mu/io/parser/target.h>

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
			class values : public mu::io::tokens::visitor, public mu::io::parser::target
			{
			public:
				values (mu::io::parser::parser & parser_a, mu::io::parser::target & target_a);
				void operator () (mu::io::tokens::divider * token) override;
				void operator () (mu::io::tokens::identifier * token) override;
				void operator () (mu::io::tokens::left_square * token) override;
				void operator () (mu::io::tokens::right_square * token) override;
				void operator () (mu::io::tokens::stream_end * token) override;
				void operator () (mu::io::tokens::parameters * token) override;
				void operator () (boost::shared_ptr <mu::io::ast::expression> expression_a) override;
				mu::io::parser::target & target;
				std::vector <boost::shared_ptr <mu::io::ast::node>> values_m;
				mu::io::parser::parser & parser;
				mu::io::debugging::context first;
			};
		}
	}
}
