#pragma once

#include <mu/script/parser/state.h>
#include <mu/io/tokens/visitor.h>

namespace mu
{
    namespace script
    {
        namespace parser
        {
            class parser;
            class cluster : mu::script::parser::state, mu::io::tokens::visitor
            {
                cluster (mu::script::parser::parser & parser_a);
                mu::script::parser::parser & parser;
                void operator () (mu::io::tokens::token * token_a, mu::io::debugging::context context_a) override;
                mu::io::debugging::context context;
				void operator () (mu::io::tokens::divider * token) override;
				void operator () (mu::io::tokens::identifier * token) override;
				void operator () (mu::io::tokens::left_square * token) override;
				void operator () (mu::io::tokens::right_square * token) override;
				void operator () (mu::io::tokens::stream_end * token) override;
				void operator () (mu::io::tokens::parameters * token) override;
                void operator () (mu::io::tokens::value * token) override;
            };
        }
    }
}