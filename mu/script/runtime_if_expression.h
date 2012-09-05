#pragma once

#include <mu/script/operation.h>

namespace mu
{
    namespace script
    {
        namespace runtime
        {
            class expression;
            class if_clause : public mu::script::operation
            {
            public:
                bool operator () (mu::script::context & context_a) override;
                mu::script::runtime::expression * predicate;
                mu::script::runtime::expression * true_branch;
                mu::script::runtime::expression * false_branch;
            };
        }
    }
}