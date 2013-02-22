#pragma once

#include <mu/core/types.hpp>
#include <mu/llvmc/instruction_type.hpp>

namespace llvm
{
    class Constant;
}
namespace mu
{
    namespace llvmc
    {        
        class analyzer_function;
        namespace ast
        {
            class node;
        }
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
            class type : virtual public mu::llvmc::skeleton::node
            {                
            };
            class branch
            {
            public:
                branch (mu::llvmc::skeleton::branch * parent_a);
                mu::llvmc::skeleton::branch * parent;
            };
            class value : virtual public mu::llvmc::skeleton::node
            {
            public:
                value (mu::llvmc::skeleton::branch * branch_a);
                virtual mu::llvmc::skeleton::type * type () = 0;
                mu::llvmc::skeleton::branch * branch;
            };
            class target : virtual public mu::llvmc::skeleton::node
            {
            public:
                virtual void process_arguments (mu::llvmc::analyzer_function & analyzer_a, mu::llvmc::ast::node * node_a, mu::vector <mu::llvmc::skeleton::node *> & arguments_a) = 0;
            };
            class parameter : public mu::llvmc::skeleton::value
            {
            public:
                parameter (mu::llvmc::skeleton::branch * branch_a, mu::llvmc::skeleton::type * type_a);
                mu::llvmc::skeleton::type * type () override;
                mu::llvmc::skeleton::type * type_m;
            };
            class constant : public mu::llvmc::skeleton::value
            {
                mu::llvmc::skeleton::type * type () override;
            };
            class instruction : public mu::llvmc::skeleton::target
            {
            public:
                instruction (mu::llvmc::instruction_type type_a);
                void process_arguments (mu::llvmc::analyzer_function & analyzer_a, mu::llvmc::ast::node * node_a, mu::vector <mu::llvmc::skeleton::node *> & arguments_a) override;
                mu::llvmc::instruction_type type;
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
            class function : public mu::llvmc::skeleton::target
            {
            public:
                function ();
                void process_arguments (mu::llvmc::analyzer_function & analyzer_a, mu::llvmc::ast::node * node_a, mu::vector <mu::llvmc::skeleton::node *> & arguments_a) override;
                mu::llvmc::skeleton::branch entry;
                mu::vector <mu::llvmc::skeleton::parameter *> parameters;
                mu::vector <mu::vector <mu::llvmc::skeleton::result *>> results;
            };
            class element : public mu::llvmc::skeleton::value
            {
            public:
                element (mu::llvmc::skeleton::branch * branch_a, mu::llvmc::skeleton::function * function_a, size_t result_index_a, size_t item_index_a);
                mu::llvmc::skeleton::type * type () override;
                mu::llvmc::skeleton::function * function;
                size_t result_index;
                size_t item_index;
            };
            class module
            {
            public:
                mu::vector <mu::llvmc::skeleton::function *> functions;
            };
        }
    }
}