#pragma once

#include <mu/io/analyzer/analyzer.h>
#include <mu/io/parser/parser.h>
#include <mu/io/lexer/lexer.h>

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
        namespace analyzer
        {
            namespace extensions
            {
                class extensions;
            }
        }
    }
    namespace script
    {
        namespace cluster
        {
            class node;
        }
        class builder
        {
        public:
			builder ();
			builder (mu::io::analyzer::extensions::extensions * extensions_a);
			void operator () (mu::io::lexer::context const & context_a);
			mu::core::errors::error_list * errors;
			mu::io::analyzer::analyzer analyzer;
			mu::io::parser::parser parser;
			mu::io::lexer::lexer lexer;
			void add (mu::core::cluster *);
			mu::script::cluster::node * cluster;
        };
    }
}