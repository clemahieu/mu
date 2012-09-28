#pragma once

#include <mu/script/parser_state.h>
#include <mu/io/tokens_visitor.h>
#include <mu/io/scope_block.h>

namespace mu
{
    namespace script
    {
        namespace ast
        {
            class routine;
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
            class routine : public mu::script::parser::state, public mu::io::tokens::visitor
            {
            public:
                routine (mu::script::parser::cluster & cluster_a);
                routine_state state;
                size_t parameters;
                mu::script::parser::cluster & cluster;
                void operator () (mu::io::tokens::token const & token_a) override;
                mu::script::ast::routine * routine_m;
                mu::io::scope::block scope;
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