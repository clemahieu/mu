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
			builder (boost::shared_ptr <mu::io::analyzer::extensions::extensions> extensions_a);
			boost::shared_ptr <mu::core::errors::error_list> errors;
			mu::io::analyzer::analyzer analyzer;
			mu::io::parser::parser parser;
			mu::io::lexer::lexer lexer;
			void add (boost::shared_ptr <mu::core::cluster>, boost::shared_ptr <mu::io::debugging::mapping>);
			std::vector <boost::shared_ptr <mu::script::cluster::node>> clusters;
        };
    }
}