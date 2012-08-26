#pragma once

#include <boost/function.hpp>

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
            enum class expression_state
            {
                values,
                name,
                have_name,
                elements
            };
            class routine;
            class expression : public mu::llvm_::parser::state, public mu::io::tokens::visitor
            {
            public:
                expression (mu::llvm_::parser::routine & routine_a);
                mu::io::context context;
                mu::llvm_::parser::expression_state state;
                mu::llvm_::parser::routine & routine;
                size_t element;
                mu::llvm_::ast::expression * expression_m;
                void operator () (mu::io::tokens::token * token_a, mu::io::context context_a) override;
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