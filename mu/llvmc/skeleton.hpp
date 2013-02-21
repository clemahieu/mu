#pragma once

#include <mu/core/types.hpp>

namespace llvm
{
    class Constant;
}
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
            class node
            {
            public:
                virtual ~node ();
            };
            class type : public mu::llvmc::skeleton::node
            {                
            };
            class branch
            {
            public:
                branch (mu::llvmc::skeleton::branch * parent_a);
                mu::llvmc::skeleton::branch * parent;
            };
            class value : public mu::llvmc::skeleton::node
            {
            public:
            };
            class local : public mu::llvmc::skeleton::value
            {
            public:
                local (mu::llvmc::skeleton::branch * branch_a);
                mu::llvmc::skeleton::branch * branch;
            };
            class call
            {
            public:                
            };
            class parameter : public mu::llvmc::skeleton::local
            {
            public:
                parameter (mu::llvmc::skeleton::branch * branch_a, mu::llvmc::skeleton::type * type_a);
                mu::llvmc::skeleton::type * type;
            };
            class element : public mu::llvmc::skeleton::local
            {
            public:
                element (mu::llvmc::skeleton::branch * branch_a, mu::llvmc::skeleton::call * call_a, size_t index_a);
                mu::llvmc::skeleton::call * call;
                size_t index;
            };
            class constant : public mu::llvmc::skeleton::value
            {
            };
            class instruction : public mu::llvmc::skeleton::local
            {
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
                result (mu::llvmc::skeleton::type * type_a, mu::llvmc::skeleton::value * value_a);
                mu::llvmc::skeleton::type * type;
                mu::llvmc::skeleton::value * value;
            };
            class function : public mu::llvmc::skeleton::value
            {
            public:
                function ();
                mu::llvmc::skeleton::branch entry;
                mu::vector <mu::llvmc::skeleton::parameter *> parameters;
                mu::vector <mu::vector <mu::llvmc::skeleton::result *>> results;
            };
            class module
            {
            public:
                mu::vector <mu::llvmc::skeleton::function *> functions;
            };
        }
    }
}