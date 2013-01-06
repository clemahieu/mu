#pragma once

#include <mu/core/types.hpp>

namespace mu
{
    namespace llvmc
    {
        namespace availability
        {      
            class node
            {
            public:
                virtual ~node ();
            };
            class context : public mu::llvmc::availability::node
            {
            public:
            };
            class module : public mu::llvmc::availability::node
            {
            public:
                mu::llvmc::availability::context * context;
            };
            class function : public mu::llvmc::availability::node
            {
            public:
                mu::llvmc::availability::module * module;
            };
            class if_branch : public mu::llvmc::availability::node
            {
            public:
                mu::llvmc::availability::node * parent;
            };
            class phi : public mu::llvmc::availability::node
            {
            public:
                mu::vector <mu::llvmc::availability::node *> incoming;
            };
            class switch_branch : public mu::llvmc::availability::node
            {
            public:
                mu::llvmc::availability::node * parent;
            };
        }
    }
}