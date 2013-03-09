#include <mu/llvmc/skeleton.hpp>

#include <mu/llvmc/analyzer.hpp>
#include <mu/core/error_string.hpp>

#include <gc_cpp.h>

mu::llvmc::skeleton::element::element (mu::llvmc::skeleton::branch * branch_a, mu::llvmc::skeleton::function_call * call_a, size_t branch_index_a, size_t result_index_a) :
value (branch_a),
call (call_a),
branch_index (branch_index_a),
result_index (result_index_a)
{
}

mu::llvmc::skeleton::node::~node ()
{
}

mu::llvmc::skeleton::function::function (mu::llvmc::skeleton::branch * global_a) :
value (nullptr),
type_m (*this),
entry (global_a)
{
}

mu::llvmc::skeleton::function_type::function_type (mu::llvmc::skeleton::function & function_a) :
function (function_a)
{
}

mu::llvmc::skeleton::branch::branch (mu::llvmc::skeleton::branch * parent_a) :
parent (parent_a)
{
}

mu::llvmc::skeleton::value::value (mu::llvmc::skeleton::branch * branch_a) :
branch (branch_a)
{
}

mu::llvmc::skeleton::integer_type::integer_type (size_t bits_a) :
bits (bits_a)
{
}

mu::llvmc::skeleton::parameter::parameter (mu::llvmc::skeleton::branch * branch_a, mu::llvmc::skeleton::type * type_a) :
value (branch_a),
type_m (type_a)
{
}

mu::llvmc::skeleton::result::result (mu::llvmc::skeleton::type * type_a, mu::llvmc::skeleton::value * value_a):
type (type_a),
value (value_a)
{
}

mu::llvmc::skeleton::instruction::instruction (mu::llvmc::skeleton::branch * branch_a, mu::vector <mu::llvmc::skeleton::node *> const & arguments_a, mu::llvmc::instruction_type type_a) :
value (branch_a),
type_m (type_a),
arguments (arguments_a)
{
}

mu::llvmc::skeleton::type * mu::llvmc::skeleton::function::type ()
{
    return & type_m;
}

mu::llvmc::skeleton::pointer_type::pointer_type (mu::llvmc::skeleton::type * type_a):
pointed_type (type_a)
{
}

mu::llvmc::skeleton::type * mu::llvmc::skeleton::element::type ()
{
    assert (call->target.results.size () > branch_index);
    assert (call->target.results [branch_index].size () > result_index);
    auto result (call->target.results [branch_index][result_index]->type);
    return result;
}

mu::llvmc::skeleton::type * mu::llvmc::skeleton::parameter::type ()
{
    auto result (type_m);
    return result;
}

bool mu::llvmc::skeleton::integer_type::operator == (mu::llvmc::skeleton::type const & other_a) const
{
    auto result (false);
    auto other_integer (dynamic_cast <mu::llvmc::skeleton::integer_type const *> (&other_a));
    if (other_integer != nullptr)
    {
        result = bits == other_integer->bits;
    }
    return result;
}

bool mu::llvmc::skeleton::function_type::operator == (mu::llvmc::skeleton::type const & other_a) const
{
    auto result (false);
    auto other_function (dynamic_cast <mu::llvmc::skeleton::function_type const *> (&other_a));
    if (other_function != nullptr)
    {
        if (function.parameters.size () == other_function->function.parameters.size ())
        {
            if (function.results.size () == other_function->function.results.size ())
            {
                result = true;
                for (auto i (function.results.begin ()), j (function.results.end ()), k (other_function->function.results.begin ()); i != j && result; ++i, ++k)
                {
                    result = i->size () == k->size ();
                    for (auto m (i->begin()), n (i->end ()), o (k->begin ()); m != n && result; ++m, ++o)
                    {
                        result = (*m) == (*o);
                    }
                }
            }
        }
    }
    return result;
}

bool mu::llvmc::skeleton::unit_type::operator == (mu::llvmc::skeleton::type const & other_a) const
{
    auto other_unit (dynamic_cast <mu::llvmc::skeleton::unit_type const *> (&other_a));
    auto result (other_unit != nullptr);
    return result;
}

bool mu::llvmc::skeleton::type::operator != (mu::llvmc::skeleton::type const & other_a) const
{
    bool result (!(*this == other_a));
    return result;
}

mu::llvmc::skeleton::function_call::function_call (mu::llvmc::skeleton::function & target_a, mu::llvmc::skeleton::branch * branch_a, mu::vector <mu::llvmc::skeleton::node *> const & arguments_a):
target (target_a),
branch (branch_a),
arguments (arguments_a)
{
}

mu::llvmc::skeleton::switch_call::switch_call (mu::llvmc::skeleton::value * target_a) :
target (target_a)
{
}

mu::llvmc::skeleton::switch_element::switch_element (mu::llvmc::skeleton::branch * branch_a, mu::llvmc::skeleton::switch_call * call_a, mu::llvmc::skeleton::value * case_a) :
value (branch_a),
call (call_a),
case_m (case_a)
{
}

mu::llvmc::skeleton::constant::constant () :
value (nullptr)
{
}

mu::llvmc::skeleton::constant_integer::constant_integer (size_t bits_a, uint64_t value_a) :
type_m (new (GC) mu::llvmc::skeleton::integer_type (bits_a)),
value_m (value_a)
{
}

mu::llvmc::skeleton::type * mu::llvmc::skeleton::constant_integer::type ()
{
    return type_m;
}

mu::llvmc::skeleton::type * mu::llvmc::skeleton::switch_element::type ()
{
    return & type_m;
}

mu::llvmc::skeleton::marker::marker (mu::llvmc::instruction_type type_a) :
type (type_a)
{
}

mu::llvmc::skeleton::type * mu::llvmc::skeleton::instruction::type ()
{
    mu::llvmc::skeleton::type * result (nullptr);
    switch (type_m)
    {
        case mu::llvmc::instruction_type::add:
        {
            assert (arguments.size () == 3);
            assert (dynamic_cast <mu::llvmc::skeleton::value *> (arguments [1]) != nullptr);
            assert (dynamic_cast <mu::llvmc::skeleton::value *> (arguments [2]) != nullptr);
            assert (*dynamic_cast <mu::llvmc::skeleton::value *> (arguments [1])->type () == *dynamic_cast <mu::llvmc::skeleton::value *> (arguments [2])->type ());
            result = static_cast <mu::llvmc::skeleton::value *> (arguments [1])->type ();
        }
            break;
        default:
            assert (false);
            break;
    }
    return result;
}

mu::llvmc::skeleton::branch * mu::llvmc::skeleton::branch::most_specific (mu::llvmc::skeleton::branch * other_a)
{
    mu::llvmc::skeleton::branch * result (nullptr);
    auto left (this);
    auto right (other_a);
    while (right != nullptr && right != left)
    {
        right = right->parent;
    }
    if (right == nullptr)
    {
        // Previous most specific branch was not above or equal to the current one
        // Either current one must be most specific branch or these arguments are disjoint which is an error
        left = other_a;
        right = this;
        while (right != nullptr && right != left)
        {
            right = right->parent;
        }
        if (right != nullptr)
        {
            result = this;
        }
    }
    else
    {
        result = other_a;
    }
    return result;
}