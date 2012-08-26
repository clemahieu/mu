#pragma once

#include <mu/llvm_/parser/state.h>

namespace mu
{
    namespace llvm_
    {
        namespace parser
        {
            class error : public mu::llvm_::parser::state
            {
                void operator () (mu::io::tokens::token * token_a, mu::io::context context_a) override;
            };
        }
    }
}