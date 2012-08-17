#pragma once

#include <mu/script/parser/state.h>
#include <mu/io/tokens/visitor.h>

namespace mu
{
    namespace core
    {
        class node_list;
    }
    namespace script
    {
        namespace runtime
        {
            class expression;
        }
        namespace parser
        {
            class routine;
            class body : public mu::script::parser::state, public mu::io::tokens::visitor
            {
            public:
                body (mu::script::parser::routine & routine_a);
                mu::script::parser::routine & routine;
                mu::io::debugging::context context;
                mu::script::runtime::expression * expression_m;
                mu::core::node_list * nodes;
                void operator () (mu::io::tokens::token * token_a, mu::io::debugging::context context_a) override;
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