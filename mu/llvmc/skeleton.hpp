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
            public:
                virtual bool operator == (mu::llvmc::skeleton::type const & other_a) const = 0;
                bool operator != (mu::llvmc::skeleton::type const & other_a) const;
                virtual bool is_bottom_type () const;
            };
            class branch
            {
            public:
                branch (mu::llvmc::skeleton::branch * parent_a);
                mu::llvmc::skeleton::branch * most_specific (mu::llvmc::skeleton::branch * other_a);
                mu::llvmc::skeleton::branch * parent;
            };
            class value : public mu::llvmc::skeleton::node
            {
            public:
                value (mu::llvmc::skeleton::branch * branch_a);
                virtual mu::llvmc::skeleton::type * type () = 0;
                mu::llvmc::skeleton::branch * branch;
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
            public:
                constant ();
            };
            class constant_integer : public mu::llvmc::skeleton::constant
            {
            public:
                constant_integer (size_t bits_a, uint64_t value_a);
                mu::llvmc::skeleton::type * type () override;
                mu::llvmc::skeleton::type * type_m;
                uint64_t value_m;
            };
            class instruction : public mu::llvmc::skeleton::value
            {
            public:
                instruction (mu::llvmc::skeleton::branch * branch_a, mu::vector <mu::llvmc::skeleton::node *> const & arguments_a, mu::vector <mu::llvmc::skeleton::node *> const & predicates_a, mu::llvmc::instruction_type type_a);
                mu::llvmc::skeleton::type * type () override;
                mu::llvmc::instruction_type type_m;
                mu::vector <mu::llvmc::skeleton::node *> arguments;
                mu::vector <mu::llvmc::skeleton::node *> predicates;
            };
            class marker : public mu::llvmc::skeleton::node
            {
            public:
                marker (mu::llvmc::instruction_type type_a);
                mu::llvmc::instruction_type type;
            };
            class integer_type : public mu::llvmc::skeleton::type
            {
            public:
                integer_type (size_t bits_a);
                bool operator == (mu::llvmc::skeleton::type const & other_a) const override;
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
                bool operator == (mu::llvmc::skeleton::type const & other_a) const override;
            };
            class bottom_type : public mu::llvmc::skeleton::type
            {
            public:
                bool operator == (mu::llvmc::skeleton::type const & other_a) const override;
                bool is_bottom_type () const override;
            };
            class result
            {
            public:
                result (mu::llvmc::skeleton::type * type_a, mu::llvmc::skeleton::value * value_a);
                mu::llvmc::skeleton::type * type;
                mu::llvmc::skeleton::value * value;
            };
            class function;
            class function_type : public mu::llvmc::skeleton::type
            {
            public:
                function_type (mu::llvmc::skeleton::function & function_a);
                bool operator == (mu::llvmc::skeleton::type const & other_a) const override;
                mu::llvmc::skeleton::function & function;
            };
            class function : public mu::llvmc::skeleton::value
            {
            public:
                function (mu::llvmc::skeleton::branch * global_a);
                mu::llvmc::skeleton::function_type type_m;
                mu::llvmc::skeleton::type * type () override;
                mu::llvmc::skeleton::branch * entry;
                mu::vector <mu::llvmc::skeleton::parameter *> parameters;
                mu::vector <mu::vector <mu::llvmc::skeleton::result *>> results;
            };
            class pointer_type : public mu::llvmc::skeleton::type
            {
            public:
                pointer_type (mu::llvmc::skeleton::type * type_a);
                mu::llvmc::skeleton::type * pointed_type;
            };
            class switch_element;
            class switch_i
            {
            public:
                switch_i (mu::llvmc::skeleton::branch * branch_a, mu::llvmc::skeleton::value * predicate_a, mu::vector <mu::llvmc::skeleton::node *> const & predicates_a);
                mu::llvmc::skeleton::branch * branch;
                mu::llvmc::skeleton::value * predicate;
                mu::vector <mu::llvmc::skeleton::node *> predicates;
                mu::vector <mu::llvmc::skeleton::switch_element *> elements;
            };
            class switch_element : public mu::llvmc::skeleton::value
            {
            public:
                switch_element (mu::llvmc::skeleton::branch * branch_a, mu::llvmc::skeleton::switch_i * source_a, mu::llvmc::skeleton::constant_integer * value_a);
                mu::llvmc::skeleton::type * type () override;
                mu::llvmc::skeleton::bottom_type type_m;
                mu::llvmc::skeleton::switch_i * source;
                mu::llvmc::skeleton::constant_integer * value_m;
            };
            class call_element;
            class function_call
            {
            public:
                function_call (mu::llvmc::skeleton::function & target_a, mu::llvmc::skeleton::branch * branch_a, mu::vector <mu::llvmc::skeleton::node *> const & arguments_a, mu::vector <mu::llvmc::skeleton::node *> const & predicates_a);
                mu::llvmc::skeleton::function & target;
                mu::llvmc::skeleton::branch * branch;
                mu::vector <mu::llvmc::skeleton::node *> arguments;
                mu::vector <mu::llvmc::skeleton::node *> predicates;
                mu::vector <mu::llvmc::skeleton::call_element *> elements;
            };
            class call_element : public mu::llvmc::skeleton::value
            {
            public:
                call_element (mu::llvmc::skeleton::branch * branch_a, mu::llvmc::skeleton::function_call * source_a, size_t branch_index_a, size_t result_index_a);
                mu::llvmc::skeleton::type * type () override;
                mu::llvmc::skeleton::function_call * source;
                size_t branch_index;
                size_t result_index;
            };
            class unit_value : public mu::llvmc::skeleton::value
            {
            public:
                unit_value (mu::llvmc::skeleton::branch * branch_a);
                mu::llvmc::skeleton::type * type () override;
                mu::llvmc::skeleton::unit_type type_m;
            };
            class bottom_value : public mu::llvmc::skeleton::value
            {
            public:
                bottom_value (mu::llvmc::skeleton::branch * branch_a);
                mu::llvmc::skeleton::type * type () override;
                mu::llvmc::skeleton::bottom_type type_m;
            };
            class module
            {
            public:
                module ();
                mu::vector <mu::llvmc::skeleton::function *> functions;
                mu::llvmc::skeleton::branch * global;
            };
        }
    }
}