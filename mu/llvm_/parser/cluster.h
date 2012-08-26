#pragma once

#include <mu/llvm_/parser/state.h>
#include <mu/io/tokens_visitor.h>
#include <mu/io/analyzer_name_map.h>

namespace mu
{
    namespace llvm_
    {
        namespace ast
        {
            class cluster;
        }
        namespace parser
        {
            class parser;
            class cluster : public mu::llvm_::parser::state, public mu::io::tokens::visitor
            {
            public:
                cluster (mu::llvm_::parser::parser & parser_a);
                mu::llvm_::parser::parser & parser;
                void operator () (mu::io::tokens::token * token_a) override;
                mu::llvm_::ast::cluster * cluster_m;
                mu::io::analyzer::name_map map;
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