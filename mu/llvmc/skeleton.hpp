#pragma once

#include <mu/core/types.hpp>

namespace mu
{
    namespace llvmc
    {
        namespace wrapper
        {
            class type;
        }
        namespace skeleton
        {
            class expression
            {
            public:
                virtual ~expression ();
            };
            class definite_expression : public mu::llvmc::skeleton::expression
            {
            public:
                mu::vector <mu::llvmc::skeleton::expression *> arguments;
            };
            class element : public mu::llvmc::skeleton::expression
            {
            public:
                element (mu::llvmc::skeleton::expression * expression_a, size_t index_a);
                mu::llvmc::skeleton::expression * expression_m;
                size_t index;
            };
            class instruction : public mu::llvmc::skeleton::expression
            {
            };
            class type : public mu::llvmc::skeleton::expression
            {
            public:
            };
            class integer_type : public mu::llvmc::skeleton::type
            {
            public:
                integer_type (size_t bits_a);
                size_t bits;
            };
            class struct_type : public mu::llvmc::skeleton::type
            {
            public:
                mu::vector <mu::llvmc::skeleton::type *> elements;
            };
            class unit_type : public mu::llvmc::skeleton::type
            {
            public:
            };
            class result
            {
            public:
                mu::llvmc::skeleton::type * type;
                mu::llvmc::skeleton::expression * expression;
            };
            class parameter : public mu::llvmc::skeleton::expression
            {
            public:
                parameter (mu::llvmc::skeleton::type * type_a);
                mu::llvmc::skeleton::type * type;
            };
            class function : public mu::llvmc::skeleton::expression
            {
            public:
                mu::vector <mu::llvmc::skeleton::parameter> parameters;
                mu::vector <mu::vector <mu::llvmc::skeleton::result>> results;
            };
            class module
            {
            public:
                mu::vector <mu::llvmc::skeleton::function *> functions;
            };
        }
    }
}