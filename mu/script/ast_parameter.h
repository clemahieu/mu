#pragma once

#include <mu/script/ast_node.h>

namespace mu
{
    namespace script
    {
        namespace ast
        {
            class parameter : public mu::script::ast::node
            {
            public:
                parameter (size_t position_a);
                size_t position;
            };
        }
    }
}