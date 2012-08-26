#pragma once

#include <mu/script/parser_state.h>
#include <mu/io/tokens_visitor.h>

namespace mu
{
    namespace script
    {
        namespace parser
        {
            class routine;
            class parameters : public mu::script::parser::state, public mu::io::tokens::visitor
            {
            public:
                parameters (mu::script::parser::routine & routine_a);
                mu::script::parser::routine & routine;
                void operator () (mu::io::tokens::token * token_a) override;
				void operator () (mu::io::tokens::divider * token) override;
				void operator () (mu::io::tokens::identifier * token) override;
				void operator () (mu::io::tokens::left_square * token) override;
				void operator () (mu::io::tokens::right_square * token) override;
				void operator () (mu::io::tokens::stream_end * token) override;
                void operator () (mu::io::tokens::value * token) override;
            };
        }
    }
}