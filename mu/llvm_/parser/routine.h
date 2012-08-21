#pragma once

#include <mu/llvm_/parser/state.h>
#include <mu/io/tokens/visitor.h>

#include <vector>
#include <set>
#include <deque>

namespace llvm
{
    class Function;
}
namespace mu
{
    namespace llvm_
    {
        namespace function
        {
            class node;
        }
        namespace value
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
                mu::string name;
                size_t parameters;
                mu::llvm_::parser::cluster & cluster;
                void operator () (mu::io::tokens::token * token_a, mu::io::debugging::context context_a) override;
                void operator () () override;
                mu::io::debugging::context context;
                mu::vector <mu::llvm_::value::node> values;
                mu::llvm_::function::node * function;
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