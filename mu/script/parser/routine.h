#pragma once

#include <mu/script/parser/state.h>
#include <mu/io/tokens/visitor.h>
#include <mu/script/runtime/routine.h>

#include <vector>
#include <set>
#include <deque>

namespace mu
{
    namespace script
    {
        namespace parser
        {
            class cluster;
            enum class routine_state
            {
                name,
                parameters,
                body
            };
            class routine : public mu::script::parser::state, public mu::io::tokens::visitor
            {
            public:
                routine (mu::script::parser::cluster & cluster_a);
                routine_state state;
                mu::string name;
                size_t parameters;
                mu::script::parser::cluster & cluster;
                void operator () (mu::io::tokens::token * token_a, mu::io::debugging::context context_a) override;
                mu::io::debugging::context context;
                mu::script::runtime::routine * routine_m;
                mu::script::runtime::expression * root;
				void operator () (mu::io::tokens::divider * token) override;
				void operator () (mu::io::tokens::identifier * token) override;
				void operator () (mu::io::tokens::left_square * token) override;
				void operator () (mu::io::tokens::right_square * token) override;
				void operator () (mu::io::tokens::stream_end * token) override;
				void operator () (mu::io::tokens::parameters * token) override;
                void operator () (mu::io::tokens::value * token) override;
                void perform_topology ();
                void topology_recurse (std::set <mu::script::runtime::expression *, std::deque <mu::script::runtime::expression *, gc_allocator <mu::script::runtime::expression *>>> & already, std::set <mu::script::runtime::expression *, std::deque <mu::script::runtime::expression *, gc_allocator<mu::script::runtime::expression *>>> & path, mu::script::runtime::expression * expression_a);
            };
        }
    }
}