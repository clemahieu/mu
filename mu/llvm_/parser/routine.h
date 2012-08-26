#pragma once

#include <mu/llvm_/parser/state.h>
#include <mu/io/tokens/visitor.h>

#include <vector>
#include <set>
#include <deque>

namespace mu
{
    namespace llvm_
    {
        namespace ast
        {
            class routine;
        }
        namespace function
        {
            class node;
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
            class routine : public mu::llvm_::parser::state, public mu::io::tokens::visitor
            {
            public:
                routine (mu::llvm_::parser::cluster & cluster_a);
                routine_state state;
                mu::llvm_::parser::cluster & cluster;
                void operator () (mu::io::tokens::token * token_a) override;
                mu::llvm_::ast::routine * routine_m;
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