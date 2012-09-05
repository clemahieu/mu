#pragma once

#include <mu/script/ast_expression.h>
#include <mu/core/node_list.h>

namespace mu
{
    namespace script
    {
        namespace ast
        {
            class if_expression : public mu::script::ast::expression
            {
            public:                
                mu::core::node_list predicate;
                mu::core::node_list true_branch;
                mu::core::node_list false_branch;
            };
        }
    }
}