#pragma once

namespace mu
{
    namespace llvm_
    {
        class ctx;
        class operation
        {
        public:
            virtual bool operator () (mu::llvm_::ctx & context_a) = 0;
        };
    }
}