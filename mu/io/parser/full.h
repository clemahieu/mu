#pragma once

#include <mu/core/context.h>
#include <mu/io/tokens/visitor.h>

#include <boost/shared_ptr.hpp>
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
			class identifier;
		}
		namespace parser
		{
			class parser;
			class full : public mu::io::tokens::visitor
			{
			public:
				full (mu::io::parser::parser & parser_a, boost::function <void (boost::shared_ptr <mu::io::ast::expression>)> target_a, std::vector <boost::shared_ptr <mu::io::ast::node>> values_a, std::vector <boost::shared_ptr <mu::io::ast::identifier>> names_a, mu::core::context first_a);
				void operator () (mu::io::tokens::divider * token) override;
				void operator () (mu::io::tokens::identifier * token) override;
				void operator () (mu::io::tokens::left_square * token) override;
				void operator () (mu::io::tokens::right_square * token) override;
				void operator () (mu::io::tokens::stream_end * token) override;
				void operator () (mu::io::tokens::parameters * token) override;
				void unexpected_token (mu::io::tokens::token * token, mu::core::context context_a);
				mu::io::parser::parser & parser;
				boost::function <void (boost::shared_ptr <mu::io::ast::expression>)> target;
				std::vector <boost::shared_ptr <mu::io::ast::node>> values;
				std::vector <boost::shared_ptr <mu::io::ast::identifier>> names;
				boost::shared_ptr <mu::io::ast::identifier> full_name;			
				mu::core::context first;
			};
		}
	}
}
