#pragma once

#include <mu/script/parser/state.h>

namespace mu
{
    namespace script
    {
        namespace parser
        {
            class error : public mu::script::parser::state
            {
                void operator () (mu::io::tokens::token * token_a) override;
            };
        }
    }
}