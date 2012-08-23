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
    namespace llvm_
    {
        namespace ast
        {
            class cluster;
        }
        namespace cluster
        {
            class node;
        }
        namespace context
        {
            class node;
        }
        namespace synthesizer
        {
            class synthesizer
            {
                synthesizer (mu::llvm_::context::node * context_a, mu::core::errors::error_target & errors_a, boost::function <void (mu::llvm_::cluster::node *)> target_a);;
                void operator () (mu::llvm_::ast::cluster * cluster_a);
                boost::function <void (mu::llvm_::cluster::node *)> target;
                mu::core::errors::error_target & errors;
                mu::llvm_::context::node * context;
            };
        }
    }
}