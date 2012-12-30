#pragma once

#include <mu/core/types.hpp>

namespace mu
{
    namespace llvmc
    {
        namespace availability
        {
            class node;
            class function;
            class module;
        }
        namespace ast
        {
            class node
            {
            public:
                virtual ~node ();
            };
            class scoped : public mu::llvmc::ast::node
            {
            public:
                scoped (mu::llvmc::availability::node * availability_a);
                mu::llvmc::availability::node * availability;
            };
            class expression : public mu::llvmc::ast::scoped
            {
            public:
                expression (mu::llvmc::availability::node * availability_a);
                mu::vector <mu::llvmc::ast::node *> arguments;
            };
            class function : public mu::llvmc::ast::scoped
            {
            public:
                function (mu::llvmc::availability::module * availability_a);
                mu::llvmc::availability::function * entry;
                mu::vector <mu::llvmc::ast::node *> parameters;
                mu::vector <mu::vector <mu::llvmc::ast::node *>> results;
            };
            class module : public mu::llvmc::ast::node
            {
            public:
                mu::vector <mu::llvmc::ast::function *> functions;
            };
        }
    }
}