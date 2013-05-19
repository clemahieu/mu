#pragma once

#include <mu/core/types.hpp>
#include <mu/llvmc/node_result.hpp>
#include <mu/llvmc/instruction_type.hpp>

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
            class unit : public mu::llvmc::ast::expression
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
                element (mu::llvmc::ast::node * node_a, size_t index_a, size_t total_a);
                mu::llvmc::ast::node * node;
                size_t index;
                size_t total;
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
                definite_expression ();
                template <typename T, typename U, typename V, typename W>
                void for_each_argument (T argument_op, U predicate_op, V transition_op, W loop_op)
                {
                    assert (predicate_position != ~0);
                    assert (predicate_position <= arguments.size ());
                    size_t predicate_position_l (predicate_position);
                    size_t index (0);
                    bool predicates (false);
                    for (auto i (arguments.begin ()), j (arguments.end ()); i != j && loop_op (); ++i, ++index)
                    {
                        assert (*i != nullptr);
                        if (!predicates && index >= predicate_position_l)
                        {
                            predicates = true;
                            transition_op (*i, index);
                        }
                        if (!predicates)
                        {
                            argument_op (*i, index);
                        }
                        else
                        {
                            predicate_op (*i, index);
                        }
                    }
                }
                void set_predicate_position ();
                mu::vector <mu::llvmc::ast::node *> arguments;
                size_t predicate_position;
            };
            class set_expression : public mu::llvmc::ast::expression
            {
            public:
                mu::vector <mu::llvmc::ast::node *> items;
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
                mu::vector <mu::llvmc::ast::node *> results;
                std::vector <size_t> branch_ends;
                std::vector <size_t> predicate_offsets;
                mu::llvmc::ast::result * as_result (mu::llvmc::ast::node * node_a);
                mu::llvmc::ast::expression * as_expression (mu::llvmc::ast::node * node_a);
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
                        assert (current_end != branch_ends.end ());
                        assert (current_predicate != predicate_offsets.end ());
                        assert (*current_predicate <= *current_end);
                        if (index == *current_predicate)
                        {
                            transition_op (results [index], index);
                            predicates = true;
                        }
                        if (!predicates)
                        {
                            result_op (as_result (results [index]), index);
                        }
                        else
                        {
                            predicate_op (as_expression (results [index]), index);
                        }
                        if (index + 1 >= *current_end)
                        {
                            if (!predicates)
                            {
                                transition_op (results [index], index);
                            }
                            branch_op (results [index], index);
                            predicates = false;
                            ++current_end;
                            ++current_predicate;
                        }
                    }
                }
                mu::vector <mu::llvmc::ast::node *> roots;
            };
            class type : public mu::llvmc::ast::node
            {
            };
            class integer_type : public mu::llvmc::ast::type
            {
            public:
                integer_type (mu::string const & bits_a);
                mu::string bits;
            };
            class pointer_type : public mu::llvmc::ast::type
            {
            public:
                pointer_type (mu::llvmc::ast::node * pointed_type_a);
                mu::llvmc::ast::node * pointed_type;
            };
            class module : public mu::llvmc::ast::node
            {
            public:
                mu::vector <mu::llvmc::ast::node *> functions;
            };
        }
    }
}