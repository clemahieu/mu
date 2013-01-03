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
            class module : public mu::llvmc::availability::node
            {
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