#pragma once

#include <mu/io/keywording_keywording.h>
#include <mu/io/lexer_lexer.h>
#include <mu/core/errors/error_list.h>
#include <mu/script/parser_parser.h>
#include <mu/script/synthesizer_synthesizer.h>

#include <vector>

namespace mu
{
    namespace core
    {
        class node;
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
        namespace keywording
        {
            class extensions;
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
			builder (mu::script::parser_scope::node * scope_a);
			void operator () (mu::io::lexer::context const & context_a);
			mu::core::errors::error_list errors;
            mu::script::parser_scope::node * scope;
            mu::script::synthesizer::synthesizer synthesizer;
			mu::script::parser::parser parser;
            mu::io::keywording::keywording keywording;
			mu::io::lexer::lexer lexer;
            std::vector <mu::script::cluster::node *> clusters;
        };
    }
}