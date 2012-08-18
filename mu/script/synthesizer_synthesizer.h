#pragma once

#include <boost/function.hpp>

namespace mu
{
    namespace script
    {
        namespace ast
        {
            class cluster;
            class expression;
            class routine;
        }
        namespace cluster
        {
            class node;
        }
        namespace synthesizer
        {
            class synthesizer
            {
            public:
                synthesizer (boost::function <void (mu::script::cluster::node *)> target_a);
                void operator () (mu::script::ast::cluster * cluster_a);
                boost::function <void (mu::script::cluster::node *)> target;
            };
        }
    }
}