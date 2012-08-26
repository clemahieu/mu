#pragma once

#include <mu/llvm_/parser/state.h>
#include <mu/io/tokens/visitor.h>

namespace mu
{
    namespace llvm_
    {
        namespace ast
        {
            class expression;
        }
        namespace parser
        {
            class routine;
            class body : public mu::llvm_::parser::state, public mu::io::tokens::visitor
            {
            public:
                body (mu::llvm_::parser::routine & routine_a);
                mu::llvm_::parser::routine & routine;
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