#pragma once

#include <mu/io/lexer/lexer.h>
#include <mu/io/parser/parser.h>
#include <mu/io/analyzer/analyzer.h>
#include <mu/io/ast/visitor.h>
#include <mu/core/errors/error_list.h>

#include <vector>

namespace mu
{
	namespace core
	{
		namespace errors
		{
			class error_list;
		}
	}
	namespace io
	{
        namespace lexer
        {
            class context;
        }
		namespace ast
		{
			class node;
			class cluster;
			class builder
			{
			public:
				builder ();
				void operator () (mu::io::lexer::context const & context_a);
				mu::core::errors::error_list errors;
				mu::io::parser::parser parser;
				mu::io::lexer::lexer lexer;
				void add (mu::io::ast::cluster * node_a);
				mu::io::ast::cluster * cluster;
			};
		}
	}
}
