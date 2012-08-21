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
                results,
                type,
                name
            };
            class parameters : public mu::llvm_::parser::state, public mu::io::tokens::visitor
            {
            public:
                parameters (mu::llvm_::parser::routine & routine_a);
                mu::llvm_::parser::routine & routine;
                mu::io::debugging::context context;
                mu::llvm_::parser::parameters_state state;
                std::vector <mu::string> names;
                mu::vector <mu::llvm_::type::node *> results;
                mu::vector <mu::llvm_::type::node *> types;
                void operator () (mu::io::tokens::token * token_a, mu::io::debugging::context context_a) override;
                void operator () () override;
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