#pragma once

namespace mu
{
    namespace core
    {
        class error;
    }
    namespace llvmc
    {
        namespace ast
        {
            class node;
        }
        class node_result
        {
        public:
            ~node_result ();
            mu::llvmc::ast::node * node;
            mu::core::error * error;
        };        
    }
}