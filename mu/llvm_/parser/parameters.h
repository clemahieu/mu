#pragma once

#include <mu/llvm_/parser/state.h>
#include <mu/io/tokens/visitor.h>

namespace mu
{
    namespace llvm_
    {
        namespace type
        {
            class node;
        }
        namespace parser
        {
            class routine;
            enum class parameters_state
            {
                parameters,
                results,
                name
            };
            class parameters : public mu::llvm_::parser::state, public mu::io::tokens::visitor
            {
            public:
                parameters (mu::llvm_::parser::routine & routine_a);
                mu::llvm_::parser::routine & routine;
                mu::llvm_::parser::parameters_state state;
                size_t position;
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