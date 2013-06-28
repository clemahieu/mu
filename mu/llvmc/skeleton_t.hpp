#pragma once

#include <mu/llvmc/skeleton.hpp>

template <typename T>
void mu::llvmc::skeleton::function::for_each_branch (T branch_op)
{
    size_t index (0);
    for (auto i (branch_ends.begin ()), j (branch_ends.end ()); i != j; ++i)
    {
        auto end (*i);
        branch_op (index, end);
        index = end;
    }
}

template <typename T, typename U, typename V, typename W, typename X>
void mu::llvmc::skeleton::function::for_each_results (T result_op, U predicate_op, V transition_op, W branch_op, X loop_predicate)
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
            predicate_op (as_value (results [index]), index);
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

template <typename T, typename U, typename V, typename W, typename X>
void mu::llvmc::skeleton::loop::for_each_results (T result_op, U predicate_op, V transition_op, W branch_op, X loop_predicate)
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
            result_op (results [index], index);
        }
        else
        {
            predicate_op (results [index], index);
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

template <typename T, typename U>
mu::llvmc::skeleton::type_visitor <T, U>::type_visitor (T type_op_a, U node_op_a) :
type_op (type_op_a),
node_op (node_op_a)
{
}

template <typename T, typename U>
void mu::llvmc::skeleton::type_visitor <T, U>::type (mu::llvmc::skeleton::type * node_a)
{
    type_op (node_a);
}

template <typename T, typename U>
void mu::llvmc::skeleton::type_visitor <T, U>::node (mu::llvmc::skeleton::node * node_a)
{
    node_op (node_a);
}