#pragma once

#include <mu/script/parser/state.h>
#include <mu/io/tokens/visitor.h>
#include <mu/script/runtime/routine.h>
#include <mu/io/analyzer/name_map.h>

#include <vector>

namespace mu
{
    namespace script
    {
        namespace parser
        {
            class parser;
            enum class routine_state
            {
                name,
                parameters,
                body,
                end
            };
            class routine : public mu::script::parser::state, public mu::io::tokens::visitor
            {
            public:
                routine (mu::script::parser::parser & parser_a);
                routine_state state;
                mu::string name;
                size_t parameters;
                mu::script::parser::parser & parser;
                void operator () (mu::io::tokens::token * token_a, mu::io::debugging::context context_a) override;
                mu::io::debugging::context context;
                mu::script::runtime::expression * parameters_m;
                mu::script::runtime::routine * routine_m;
                mu::io::analyzer::name_map map;
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