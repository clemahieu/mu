#pragma once

#include <mu/llvmc/ast.hpp>

template <typename S, typename T, typename U, typename V, typename W>
void mu::llvmc::ast::for_each_argument (S arguments, size_t predicate_position, T argument_op, U predicate_op, V transition_op, W loop_op)
{
    assert (predicate_position != ~0);
    assert (predicate_position <= arguments.size ());
    size_t index (0);
    bool predicates (false);
    for (auto i (arguments.begin ()), j (arguments.end ()); i != j && loop_op (); ++i, ++index)
    {
        assert (*i != nullptr);
        if (!predicates && index >= predicate_position)
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

template <typename T, typename U, typename V, typename W, typename X>
void mu::llvmc::ast::loop::for_each_results (T result_op, U predicate_op, V transition_op, W branch_op, X loop_predicate)
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
            result_op (as_expression (results [index]), index);
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

template <typename T, typename U, typename V, typename W, typename X>
void mu::llvmc::ast::function::for_each_results (T result_op, U predicate_op, V transition_op, W branch_op, X loop_predicate)
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
            auto result (maybe_result (results [index]));
            result_op (result, index);
        }
        else
        {
            auto expression (maybe_expression (results [index]));
            predicate_op (expression, index);
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