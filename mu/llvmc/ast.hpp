#pragma once

#include <mu/core/types.hpp>
#include <mu/llvmc/node_result.hpp>

namespace mu
{
    namespace io
    {
        template <typename T>
        class stream;
        class token;
    }
    namespace llvmc
    {
        namespace availability
        {
            class node;
            class function;
            class module;
        }
        namespace skeleton
        {
            class node;
        }
        namespace ast
        {
            class node
            {
            public:
                virtual ~node ();
            };
            class value : public mu::llvmc::ast::node
            {
            public:
                value (mu::llvmc::skeleton::node * node_a);
                mu::llvmc::skeleton::node * node_m;
            };
            class loop_parameter : public mu::llvmc::ast::node
            {
            public:
            };
            class result : public mu::llvmc::ast::node
            {
            public:
                result (mu::llvmc::ast::node * written_type_a);
                mu::llvmc::ast::node * written_type;
                mu::llvmc::ast::node * value;
            };
            class expression : public mu::llvmc::ast::node
            {
            };
            class parameter : public mu::llvmc::ast::expression
            {
            public:
                parameter (mu::llvmc::ast::node * type_a);
                mu::llvmc::ast::node * type;
            };
            class element : public mu::llvmc::ast::expression
            {
            public:
                element (mu::llvmc::ast::node * node_a, size_t index_a);
                mu::llvmc::ast::node * node;
                size_t index;
            };
            class loop : public mu::llvmc::ast::expression
            {
            public:
                mu::vector <mu::llvmc::ast::node *> arguments;
                mu::vector <mu::llvmc::ast::node *> parameters;
                mu::vector <mu::llvmc::ast::node *> roots;
                mu::vector <mu::vector <mu::llvmc::ast::node *>> results;
            };
            class definite_expression : public mu::llvmc::ast::expression
            {
            public:
                mu::vector <mu::llvmc::ast::node *> arguments;
            };
            class if_expression : public mu::llvmc::ast::expression
            {
            public:
                mu::llvmc::ast::node * predicate;
                mu::vector <mu::llvmc::ast::node *> true_roots;
                mu::vector <mu::llvmc::ast::node *> false_roots;
            };
            class function : public mu::llvmc::ast::node
            {
            public:
                mu::llvmc::availability::function * entry;
                mu::string name;
                mu::vector <mu::llvmc::ast::parameter *> parameters;
                mu::vector <mu::vector <mu::llvmc::ast::result *>> results;
                mu::vector <mu::llvmc::ast::node *> roots;
            };
            class module : public mu::llvmc::ast::node
            {
            public:
                mu::vector <mu::llvmc::ast::node *> functions;
            };
        }
    }
}