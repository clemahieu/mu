#pragma once

#include <mu/llvm_/parser_state.h>
#include <mu/io/tokens_visitor.h>

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
				void operator () (mu::io::tokens::divider const & token) override;
				void operator () (mu::io::tokens::identifier const & token) override;
				void operator () (mu::io::tokens::left_square const & token) override;
				void operator () (mu::io::tokens::right_square const & token) override;
				void operator () (mu::io::tokens::stream_end const & token) override;
                void operator () (mu::io::tokens::value const & token) override;
            };
        }
    }
}