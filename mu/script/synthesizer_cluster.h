#pragma once

#include <boost/function.hpp>

namespace mu
{
    namespace script
    {
        namespace ast
        {
            class cluster;
        }
        namespace cluster
        {
            class node;
        }
        namespace synthesizer
        {
            class cluster
            {
            public:
                cluster (boost::function <void (mu::script::cluster::node *)> target_a, mu::script::ast::cluster * cluster_a);
                boost::function <void (mu::script::cluster::node *)> target;
                mu::script::ast::cluster * cluster_m;
            };
        }
    }
}