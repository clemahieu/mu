#pragma once

#include <boost/function.hpp>

namespace mu
{
    namespace core
    {
        namespace errors
        {
            class error_target;
        }
    }
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
                synthesizer (mu::core::errors::error_target & errors_a, boost::function <void (mu::script::cluster::node *)> target_a);;
                void operator () (mu::script::ast::cluster * cluster_a);
                boost::function <void (mu::script::cluster::node *)> target;
                mu::core::errors::error_target & errors;
            };
        }
    }
}