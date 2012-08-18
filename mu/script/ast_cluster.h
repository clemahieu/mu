#pragma once

#include <mu/script/ast_node.h>
#include <mu/core/types.h>

namespace mu
{
    namespace script
    {
        namespace ast
        {
            class routine;
            class cluster : public mu::script::ast::node
            {
            public:
                mu::vector <mu::script::ast::routine *> routines;
            };
        }
    }
}