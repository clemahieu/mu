#pragma once

#include <mu/script/operation.h>

namespace mu
{
    namespace script
    {
        namespace runtime
        {
            class definite_expression;
            class if_expression : public mu::script::operation
            {
            public:
                bool operator () (mu::script::context & context_a) override;
                mu::script::runtime::definite_expression * predicate;
                mu::script::runtime::definite_expression * true_branch;
                mu::script::runtime::definite_expression * false_branch;
            };
        }
    }
}