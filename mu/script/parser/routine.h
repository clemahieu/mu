#pragma once

#include <mu/script/parser/state.h>
#include <mu/io/tokens/visitor.h>

#include <vector>
#include <set>
#include <deque>

namespace mu
{
    namespace script
    {
        namespace ast
        {
            class routine;
        }
        namespace parser
        {
            class cluster;
            enum class routine_state
            {
                name,
                parameters,
                body,
                have_body
            };
            class routine : public mu::script::parser::state, public mu::io::tokens::visitor
            {
            public:
                routine (mu::script::parser::cluster & cluster_a);
                routine_state state;
                size_t parameters;
                mu::script::parser::cluster & cluster;
                void operator () (mu::io::tokens::token * token_a, mu::io::context context_a) override;
                mu::io::context context;
                mu::script::ast::routine * routine_m;
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