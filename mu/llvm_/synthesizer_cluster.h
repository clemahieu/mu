#pragma once

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
        namespace synthesizer
        {
            class cluster
            {
            public:
                cluster (mu::core::errors::error_target & errors_a, mu::llvm_::ast::cluster * cluster_a);
                mu::llvm_::cluster::node * cluster_m;
            };
        }
    }
}