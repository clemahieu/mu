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
                virtual bool is_unit_type () const;
            };
            class branch
            {
            public:
                branch (mu::llvmc::skeleton::branch * parent_a);
                mu::llvmc::skeleton::branch * most_specific (mu::llvmc::skeleton::branch * other_a);
                mu::llvmc::skeleton::branch * least_specific (mu::llvmc::skeleton::branch * other_a);
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
            class constant_aggregate_zero : public mu::llvmc::skeleton::constant
            {
            public:
                constant_aggregate_zero (mu::llvmc::skeleton::type * type_a);
                mu::llvmc::skeleton::type * type () override;
                mu::llvmc::skeleton::type * type_m;
            };
            class constant_pointer_null : public mu::llvmc::skeleton::constant
            {
            public:
                constant_pointer_null (mu::llvmc::skeleton::type * type_a);
                mu::llvmc::skeleton::type * type () override;
                mu::llvmc::skeleton::type * type_m;
            };
            class instruction : public mu::llvmc::skeleton::value
            {
            public:
                instruction (mu::llvmc::skeleton::branch * branch_a, mu::vector <mu::llvmc::skeleton::node *> const & arguments_a);
                mu::llvmc::skeleton::type * type () override;
                mu::llvmc::instruction_type marker ();
                mu::vector <mu::llvmc::skeleton::node *> arguments;
            };
            class join : public mu::llvmc::skeleton::node
            {                
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
                bool is_unit_type () const override;
            };
            class result : public mu::llvmc::skeleton::node
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
                function_type (mu::llvmc::skeleton::function * function_a);
                bool operator == (mu::llvmc::skeleton::type const & other_a) const override;
                mu::llvmc::skeleton::function * function;
            };
            enum class function_return_type
            {
                b0, // Unreachable
                b1v0, // Void
                b1v1, // Single value
                b1vm, // Struct no selector
                bmv0, // Selector value
                bmvm // struct with selector
            };
            class function : public mu::llvmc::skeleton::value
            {
            public:
                function (mu::llvmc::skeleton::branch * global_a);
                size_t branch_size (size_t index) const;
                mu::llvmc::skeleton::function_return_type get_return_type ();
                mu::llvmc::skeleton::function_type type_m;
                mu::llvmc::skeleton::type * type () override;
                mu::llvmc::skeleton::branch * entry;
                mu::vector <mu::llvmc::skeleton::parameter *> parameters;
                mu::vector <mu::llvmc::skeleton::result *> results;
                std::vector <size_t> branch_ends;
                std::vector <size_t> predicate_offsets;
                template <typename T>
                void for_each_branch (T branch_op)
                {
                    size_t index (0);
                    for (auto i (branch_ends.begin ()), j (branch_ends.end ()); i != j; ++i)
                    {
                        auto end (*i);
                        branch_op (index, end);
                        index = end;
                    }
                }
                mu::llvmc::skeleton::result * as_result (mu::llvmc::skeleton::node * node_a);
                mu::llvmc::skeleton::value * as_value (mu::llvmc::skeleton::node * node_a);
                template <typename T, typename U, typename V, typename W, typename X>
                void for_each_results (T result_op, U predicate_op, V transition_op, W branch_op, X loop_predicate)
                {
                    assert (branch_ends.size () == predicate_offsets.size ());
                    size_t index (0);
                    size_t end (results.size ());
                    auto current_end (branch_ends.begin ());
                    auto current_predicate (predicate_offsets.begin ());
                    auto predicates (false);
                    for (; index != end && loop_predicate (); ++index)
                    {
                        if (!predicates)
                        {
                            result_op (as_result (results [index]), index);
                        }
                        else
                        {
                            predicate_op (as_value (results [index]), index);
                        }
                        if (index + 1 >= *current_predicate)
                        {
                            transition_op (results [index], index);
                            predicates = true;
                        }
                        if (index + 1 >= *current_end)
                        {
                            branch_op (results [index], index);
                            predicates = false;
                            ++current_end;
                            ++current_predicate;
                        }
                    }
                }
            };
            class pointer_type : public mu::llvmc::skeleton::type
            {
            public:
                pointer_type (mu::llvmc::skeleton::type * type_a);
                bool operator == (mu::llvmc::skeleton::type const & other_a) const override;
                mu::llvmc::skeleton::type * pointed_type;
            };
            class switch_element;
            class switch_i
            {
            public:
                switch_i (mu::llvmc::skeleton::branch * branch_a, mu::vector <mu::llvmc::skeleton::node *> const & arguments_a);
                mu::llvmc::skeleton::branch * branch;
                mu::vector <mu::llvmc::skeleton::node *> arguments;
                mu::vector <mu::llvmc::skeleton::switch_element *> elements;
            };
            class switch_element : public mu::llvmc::skeleton::value
            {
            public:
                switch_element (mu::llvmc::skeleton::branch * branch_a, mu::llvmc::skeleton::switch_i * source_a, mu::llvmc::skeleton::constant_integer * value_a);
                mu::llvmc::skeleton::type * type () override;
                mu::llvmc::skeleton::switch_i * source;
                mu::llvmc::skeleton::constant_integer * value_m;
            };
            class call_element;
            class function_call
            {
            public:
                function_call (mu::llvmc::skeleton::function * target_a, mu::llvmc::skeleton::branch * branch_a, mu::vector <mu::llvmc::skeleton::node *> const & arguments_a);
                mu::llvmc::skeleton::function * target;
                mu::llvmc::skeleton::branch * branch;
                mu::vector <mu::llvmc::skeleton::node *> arguments;
                mu::vector <mu::llvmc::skeleton::call_element *> elements;
            };
            class call_element : public mu::llvmc::skeleton::value
            {
            public:
                call_element (mu::llvmc::skeleton::branch * branch_a);
            };
            class call_element_value : public mu::llvmc::skeleton::call_element
            {
            public:
                call_element_value (mu::llvmc::skeleton::branch * branch_a, mu::llvmc::skeleton::function_call * source_a, size_t index_a);
                mu::llvmc::skeleton::type * type () override;
                mu::llvmc::skeleton::function_call * source;
                size_t index;
            };
            class call_element_unit : public mu::llvmc::skeleton::call_element
            {
            public:
                call_element_unit (mu::llvmc::skeleton::branch * branch_a, mu::llvmc::skeleton::function_call * source_a, size_t index_a);
                mu::llvmc::skeleton::type * type () override;
                mu::llvmc::skeleton::function_call * source;
                size_t index;
            };
            class unit_value : public mu::llvmc::skeleton::value
            {
            public:
                unit_value (mu::llvmc::skeleton::branch * branch_a);
                mu::llvmc::skeleton::type * type () override;
            };
            class join_value : public mu::llvmc::skeleton::value
            {
            public:
                join_value (mu::llvmc::skeleton::branch * branch_a, mu::vector <mu::llvmc::skeleton::value *> const & arguments_a);
                mu::llvmc::skeleton::type * type () override;
                mu::vector <mu::llvmc::skeleton::value *> arguments;
            };
            class module
            {
            public:
                module ();
                mu::vector <mu::llvmc::skeleton::function *> functions;
                mu::llvmc::skeleton::branch * global;
            };
            extern mu::llvmc::skeleton::unit_type the_unit_type;
        }
    }
}