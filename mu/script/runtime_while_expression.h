#pragma once

#include <mu/script/runtime_expression.h>

namespace mu
{
    namespace script
    {
        namespace runtime
        {
            class while_expression : public mu::script::runtime::expression
            {
            public:
                bool operator () (mu::script::context & context_a) override;
                mu::vector <mu::script::operation *> arguments;
                mu::vector <mu::script::operation *> predicate;
                mu::vector <mu::script::operation *> body;
            };
        }
    }
}
