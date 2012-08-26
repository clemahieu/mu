#pragma once

#include <mu/io/ast/node.h>

namespace mu
{
    namespace core
    {
        class node;
    }
    namespace io
    {
        namespace ast
        {
            class value : public mu::io::ast::node
            {
            public:
                value (mu::core::node * node_a, mu::io::context const & context_a);
				void operator () (mu::io::ast::visitor * visitor_a) override;
				mu::string name () override;
                mu::core::node * node_m;
            };
        }
    }
}