#pragma once

#include <mu/script/parser/state.h>
#include <mu/io/tokens/visitor.h>
#include <mu/io/analyzer/name_map.h>

namespace mu
{
    namespace script
    {
        namespace cluster
        {
            class node;
        }
        namespace parser
        {
            class parser;
            class cluster : public mu::script::parser::state, public mu::io::tokens::visitor
            {
            public:
                cluster (mu::script::parser::parser & parser_a);
                mu::script::parser::parser & parser;
                void operator () (mu::io::tokens::token * token_a, mu::io::debugging::context context_a) override;
                mu::io::debugging::context context;
                mu::io::analyzer::name_map map;
                mu::script::cluster::node * cluster_m;
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