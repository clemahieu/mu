#pragma once

#include <mu/llvm_/parser_state.h>
#include <mu/io/tokens_visitor.h>
#include <mu/io/scope_global.h>

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
                mu::io::scope::global scope;
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