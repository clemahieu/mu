#include <mu/llvmc/skeleton.hpp>

#include <mu/llvmc/analyzer.hpp>
#include <mu/core/error_string.hpp>

#include <gc_cpp.h>

mu::llvmc::skeleton::switch_i::switch_i (mu::llvmc::skeleton::branch * branch_a, mu::vector <mu::llvmc::skeleton::node *> const & arguments_a) :
branch (branch_a),
arguments (arguments_a)
{
}

mu::llvmc::skeleton::call_element::call_element (mu::llvmc::skeleton::branch * branch_a, mu::llvmc::skeleton::function_call * source_a, size_t index_a) :
value (branch_a),
source (source_a),
index (index_a)
{
}

mu::llvmc::skeleton::node::~node ()
{
}

mu::llvmc::skeleton::function::function (mu::llvmc::skeleton::branch * global_a) :
value (nullptr),
type_m (this),
entry (new (GC) mu::llvmc::skeleton::branch (global_a))
{
}

mu::llvmc::skeleton::function_type::function_type (mu::llvmc::skeleton::function * function_a) :
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

mu::llvmc::skeleton::instruction::instruction (mu::llvmc::skeleton::branch * branch_a, mu::vector <mu::llvmc::skeleton::node *> const & arguments_a) :
value (branch_a),
arguments (arguments_a)
{
    assert (arguments_a.size () > 0);
    assert (dynamic_cast <mu::llvmc::skeleton::marker *> (arguments_a [0]) != nullptr);
}

mu::llvmc::instruction_type mu::llvmc::skeleton::instruction::marker ()
{
    assert (arguments.size () > 0);
    assert (dynamic_cast <mu::llvmc::skeleton::marker *> (arguments [0]) != nullptr);
    auto result (static_cast <mu::llvmc::skeleton::marker *> (arguments [0])->type);
    return result;
}

mu::llvmc::skeleton::join_value::join_value (mu::llvmc::skeleton::branch * branch_a, mu::vector <mu::llvmc::skeleton::value *> const &arguments_a) :
value (branch_a),
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

size_t mu::llvmc::skeleton::function::branch_size (size_t index) const
{
    assert (index < branch_offsets.size ());
    auto size (branch_offsets.size ());
    size_t result;
    if (index == size - 1)
    {
        result = results.size () - branch_offsets [index];
        assert (branch_offsets [index] + result <= results.size ());
    }
    else
    {
        result = branch_offsets [index + 1] - branch_offsets [index];
        assert (branch_offsets [index] + result <= results.size ());
    }
    return result;
}

mu::llvmc::skeleton::type * mu::llvmc::skeleton::call_element::type ()
{
    assert (source->target->results.size () > index);
    auto result (source->target->results [index]->type);
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

auto mu::llvmc::skeleton::function::branch_begin (size_t index) -> decltype (results)::iterator
{
    assert (branch_offsets.size () > index);
    return results.begin () + branch_offsets [index];
}

auto mu::llvmc::skeleton::function::branch_end (size_t index) -> decltype (results)::iterator
{
    assert (branch_offsets.size () > index);
    return results.begin () + branch_offsets [index] + branch_size (index);
}

auto mu::llvmc::skeleton::function::branch_begin (size_t index) const -> decltype (results)::const_iterator
{
    assert (branch_offsets.size () > index);
    return results.begin () + branch_offsets [index];
}

auto mu::llvmc::skeleton::function::branch_end (size_t index) const -> decltype (results)::const_iterator
{
    assert (branch_offsets.size () > index);
    return results.begin () + branch_offsets [index] + branch_size (index);
}

bool mu::llvmc::skeleton::function_type::operator == (mu::llvmc::skeleton::type const & other_a) const
{
    auto result (false);
    auto other_function (dynamic_cast <mu::llvmc::skeleton::function_type const *> (&other_a));
    if (other_function != nullptr)
    {
        if (function->parameters.size () == other_function->function->parameters.size ())
        {
            if (function->results.size () == other_function->function->results.size ())
            {
                if (function->branch_offsets.size () == other_function->function->branch_offsets.size ())
                {
                    result = true;
                    for (auto i (function->branch_offsets.begin ()), j (function->branch_offsets.end ()), k (other_function->function->branch_offsets.begin ()); i != j && result; ++i, ++k)
                    {
                        result = (*i) == (*k);
                    }
                    for (auto i (function->results.begin ()), j (function->results.end ()), k (other_function->function->results.begin ()); i != j && result; ++i, ++k)
                    {
                        result = (*(*i)->type) == (*(*k)->type);
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

mu::llvmc::skeleton::function_return_type mu::llvmc::skeleton::function::get_return_type ()
{
    mu::llvmc::skeleton::function_return_type result;
    size_t llvm_values (0);
    for (auto i (results.begin ()), j (results.end ()); i != j && llvm_values < 2; ++i)
    {
        if (!(*i)->type->is_bottom_type ())
        {
            ++llvm_values;
        }
    }
    switch (branch_offsets.size ())
    {
        case 0:
            result = mu::llvmc::skeleton::function_return_type::b0;
            break;
        case 1:
        {
            switch (llvm_values)
            {
                case 0:
                    result = mu::llvmc::skeleton::function_return_type::b1v0;
                    break;
                case 1:
                    result = mu::llvmc::skeleton::function_return_type::b1v1;
                    break;
                default:
                    result = mu::llvmc::skeleton::function_return_type::b1vm;
                    break;
            }
            break;
        }
        default:
        {
            switch (llvm_values)
            {
                case 0:
                    result = mu::llvmc::skeleton::function_return_type::bmv0;
                    break;
                default:
                    result = mu::llvmc::skeleton::function_return_type::bmvm;
                    break;
            }
            break;
        }
    }
    return result;
}

mu::llvmc::skeleton::function_call::function_call (mu::llvmc::skeleton::function * target_a, mu::llvmc::skeleton::branch * branch_a, mu::vector <mu::llvmc::skeleton::node *> const & arguments_a):
target (target_a),
branch (branch_a),
arguments (arguments_a)
{
}

mu::llvmc::skeleton::switch_element::switch_element (mu::llvmc::skeleton::branch * branch_a, mu::llvmc::skeleton::switch_i * source_a, mu::llvmc::skeleton::constant_integer * value_a) :
value (branch_a),
source (source_a),
value_m (value_a)
{
    source_a->elements.push_back (this);
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

mu::llvmc::skeleton::marker::marker (mu::llvmc::instruction_type type_a) :
type (type_a)
{
}

mu::llvmc::skeleton::constant_aggregate_zero::constant_aggregate_zero (mu::llvmc::skeleton::type * type_a) :
type_m (type_a)
{
}

mu::llvmc::skeleton::type * mu::llvmc::skeleton::constant_aggregate_zero::type ()
{
    return type_m;
}

bool mu::llvmc::skeleton::pointer_type::operator == (mu::llvmc::skeleton::type const & other_a) const
{
    auto other_l (dynamic_cast <mu::llvmc::skeleton::pointer_type const *> (&other_a));
    auto result (other_l != nullptr);
    if (result)
    {
        result = *pointed_type == (*other_l);
    }
    return result;
}

mu::llvmc::skeleton::constant_pointer_null::constant_pointer_null (mu::llvmc::skeleton::type * type_a) :
type_m (type_a)
{
}

mu::llvmc::skeleton::type * mu::llvmc::skeleton::constant_pointer_null::type ()
{
    return type_m;
}

mu::llvmc::skeleton::type * mu::llvmc::skeleton::instruction::type ()
{
    mu::llvmc::skeleton::type * result (nullptr);
    switch (marker ())
    {
        case mu::llvmc::instruction_type::add:
        {
            assert (arguments.size () == 3 || (arguments.size () > 3 && arguments [3] == nullptr));
            assert (dynamic_cast <mu::llvmc::skeleton::value *> (arguments [1]) != nullptr);
            assert (dynamic_cast <mu::llvmc::skeleton::value *> (arguments [2]) != nullptr);
            assert (*dynamic_cast <mu::llvmc::skeleton::value *> (arguments [1])->type () == *dynamic_cast <mu::llvmc::skeleton::value *> (arguments [2])->type ());
            result = static_cast <mu::llvmc::skeleton::value *> (arguments [1])->type ();
            break;
        }
        case mu::llvmc::instruction_type::load:
        {
            assert (arguments.size () == 2 || (arguments.size () > 2 && arguments [2] == nullptr));
            assert (dynamic_cast <mu::llvmc::skeleton::value *> (arguments [1]) != nullptr);
            result = static_cast <mu::llvmc::skeleton::value *> (arguments [1])->type ();
            break;
        }
        default:
            assert (false);
            break;
    }
    return result;
}

mu::llvmc::skeleton::branch * mu::llvmc::skeleton::branch::least_specific (mu::llvmc::skeleton::branch * other_a)
{
    auto result (most_specific (other_a) == this ? other_a : this);
    return result;
}

mu::llvmc::skeleton::type * mu::llvmc::skeleton::join_value::type ()
{
    auto result (arguments [0]->type ());
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

bool mu::llvmc::skeleton::type::is_bottom_type () const
{
    return false;
}

bool mu::llvmc::skeleton::bottom_type::operator == (mu::llvmc::skeleton::type const & other_a) const
{
    auto result (other_a.is_bottom_type ());
    return result;
}

bool mu::llvmc::skeleton::bottom_type::is_bottom_type () const
{
    return true;
}

mu::llvmc::skeleton::type * mu::llvmc::skeleton::switch_element::type ()
{
    return & type_m;
}

mu::llvmc::skeleton::type * mu::llvmc::skeleton::unit_value::type ()
{
    return & type_m;
}

mu::llvmc::skeleton::type * mu::llvmc::skeleton::bottom_value::type ()
{
    return & type_m;
}

mu::llvmc::skeleton::unit_value::unit_value (mu::llvmc::skeleton::branch * branch_a) :
value (branch_a)
{
}

mu::llvmc::skeleton::bottom_value::bottom_value (mu::llvmc::skeleton::branch * branch_a) :
value (branch_a)
{
}

mu::llvmc::skeleton::module::module () :
global (new (GC) mu::llvmc::skeleton::branch (nullptr))
{
}