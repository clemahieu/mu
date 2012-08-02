#pragma once

#include <mu/script/parser/state.h>

namespace mu
{
    namespace script
    {
        namespace parser
        {
            class values : mu::script::parser::state
            {
                void operator () (mu::io::tokens::token * token_a, mu::io::debugging::context context_a) override;
            };
        }
    }
}