#include <mu/llvmc/skeleton.hpp>

#include <mu/llvmc/analyzer.hpp>
#include <mu/core/error_string.hpp>

#include <gc_cpp.h>

void mu::llvmc::skeleton::function::empty_node (mu::llvmc::skeleton::node *, size_t)
{
}

bool mu::llvmc::skeleton::function::empty_loop_predicate ()
{
    return true;
}

void mu::llvmc::skeleton::loop::empty_node (mu::llvmc::skeleton::node *, size_t)
{
}

bool mu::llvmc::skeleton::loop::empty_loop_predicate ()
{
    return true;
}

mu::llvmc::skeleton::result * mu::llvmc::skeleton::function::as_result (mu::llvmc::skeleton::node * node_a)
{
    assert (dynamic_cast <mu::llvmc::skeleton::result *> (node_a) != nullptr);
    auto result (static_cast <mu::llvmc::skeleton::result *> (node_a));
    return result;
}

mu::llvmc::skeleton::value * mu::llvmc::skeleton::function::as_value (mu::llvmc::skeleton::node * node_a)
{
    assert (dynamic_cast <mu::llvmc::skeleton::value *> (node_a) != nullptr);
    auto result (static_cast <mu::llvmc::skeleton::value *> (node_a));
    return result;
}

mu::llvmc::skeleton::switch_i::switch_i (mu::llvmc::skeleton::branch * branch_a, mu::vector <mu::llvmc::skeleton::node *> const & arguments_a) :
branch (branch_a),
arguments (arguments_a)
{
}

mu::llvmc::skeleton::call_element::call_element (mu::llvmc::skeleton::branch * branch_a) :
value (branch_a)
{
}

mu::llvmc::skeleton::call_element_value::call_element_value (mu::llvmc::skeleton::branch * branch_a, mu::llvmc::skeleton::function_call * source_a, size_t index_a) :
call_element (branch_a),
source (source_a),
index (index_a)
{
}

mu::llvmc::skeleton::call_element_unit::call_element_unit (mu::llvmc::skeleton::branch * branch_a, mu::llvmc::skeleton::function_call * source_a, size_t index_a) :
call_element (branch_a),
source (source_a),
index (index_a)
{
}

mu::llvmc::skeleton::node::~node ()
{
}

mu::llvmc::skeleton::function::function (mu::llvmc::skeleton::branch * global_a) :
value (global_a),
type_m (this),
pointer_type_m (&type_m),
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

mu::llvmc::skeleton::instruction::instruction (mu::llvmc::skeleton::branch * branch_a, mu::vector <mu::llvmc::skeleton::node *> const & arguments_a, size_t predicate_position_a) :
value (branch_a),
arguments (arguments_a),
predicate_position (predicate_position_a)
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
    return & pointer_type_m;
}

mu::llvmc::skeleton::pointer_type::pointer_type (mu::llvmc::skeleton::type * type_a):
pointed_type (type_a)
{
}

size_t mu::llvmc::skeleton::function::branch_size (size_t index) const
{
    assert (index < branch_ends.size ());
    auto size (branch_ends.size ());
    size_t result;
    if (index == 0)
    {
        result = branch_ends [index];
    }
    else
    {
        result = branch_ends [index] - branch_ends [index - 1];
    }
    return result;
}

mu::llvmc::skeleton::type * mu::llvmc::skeleton::call_element_unit::type ()
{
    return & mu::llvmc::skeleton::the_unit_type;
}

mu::llvmc::skeleton::type * mu::llvmc::skeleton::call_element_value::type ()
{
    assert (source->target->results.size () > index);
    auto result (source->target->as_result (source->target->results [index])->type);
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
        if (function->parameters.size () == other_function->function->parameters.size ())
        {
            if (function->results.size () == other_function->function->results.size ())
            {
                if (function->branch_ends.size () == other_function->function->branch_ends.size ())
                {
                    result = true;
                    for (auto i (function->branch_ends.begin ()), j (function->branch_ends.end ()), k (other_function->function->branch_ends.begin ()); i != j && result; ++i, ++k)
                    {
                        result = (*i) == (*k);
                    }
                    function->for_each_results (
                    [&]
                    (mu::llvmc::skeleton::result * result_a, size_t index_a)
                    {
                        result = (*result_a->type) == (*function->as_result (other_function->function->results [index_a])->type);
                    }
                    );
                }
            }
        }
    }
    return result;
}

bool mu::llvmc::skeleton::unit_type::operator == (mu::llvmc::skeleton::type const & other_a) const
{
    auto result (other_a.is_unit_type ());
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
    for_each_results (
        [&]
        (mu::llvmc::skeleton::result * result_a, size_t)
        {
            if (!result_a->type->is_unit_type ())
            {
                ++llvm_values;
            }
        }
    );
    switch (branch_ends.size ())
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

mu::llvmc::skeleton::function_call::function_call (mu::llvmc::skeleton::function * target_a, mu::llvmc::skeleton::branch * branch_a, mu::vector <mu::llvmc::skeleton::node *> const & arguments_a, size_t predicate_offset_a):
target (target_a),
branch (branch_a),
arguments (arguments_a),
predicate_offset (predicate_offset_a)
{
}

mu::llvmc::skeleton::switch_element::switch_element (mu::llvmc::skeleton::branch * branch_a, mu::llvmc::skeleton::switch_i * source_a, mu::llvmc::skeleton::constant_integer * value_a) :
value (branch_a),
source (source_a),
value_m (value_a)
{
    source_a->elements.push_back (this);
}

mu::llvmc::skeleton::constant::constant (mu::llvmc::skeleton::branch * branch_a) :
value (branch_a)
{
}

mu::llvmc::skeleton::constant_integer::constant_integer (mu::llvmc::skeleton::branch * branch_a, size_t bits_a, uint64_t value_a) :
constant (branch_a),
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

mu::llvmc::skeleton::constant_aggregate_zero::constant_aggregate_zero (mu::llvmc::skeleton::branch * branch_a, mu::llvmc::skeleton::type * type_a) :
constant (branch_a),
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

mu::llvmc::skeleton::constant_pointer_null::constant_pointer_null (mu::llvmc::skeleton::branch * branch_a, mu::llvmc::skeleton::type * type_a) :
constant (branch_a),
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
            assert (predicate_position == 3);
            assert (dynamic_cast <mu::llvmc::skeleton::value *> (arguments [1]) != nullptr);
            assert (dynamic_cast <mu::llvmc::skeleton::value *> (arguments [2]) != nullptr);
            assert (*dynamic_cast <mu::llvmc::skeleton::value *> (arguments [1])->type () == *dynamic_cast <mu::llvmc::skeleton::value *> (arguments [2])->type ());
            result = static_cast <mu::llvmc::skeleton::value *> (arguments [1])->type ();
            break;
        }
        case mu::llvmc::instruction_type::icmp:
        {
            result = & mu::llvmc::skeleton::integer_1_type;
            break;
        }
        case mu::llvmc::instruction_type::load:
        {
            assert (predicate_position == 2);
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

bool mu::llvmc::skeleton::type::is_unit_type () const
{
    return false;
}

bool mu::llvmc::skeleton::unit_type::is_unit_type () const
{
    return true;
}

mu::llvmc::skeleton::type * mu::llvmc::skeleton::switch_element::type ()
{
    return & mu::llvmc::skeleton::the_unit_type;
}

mu::llvmc::skeleton::type * mu::llvmc::skeleton::unit_value::type ()
{
    return & mu::llvmc::skeleton::the_unit_type;
}

mu::llvmc::skeleton::unit_value::unit_value (mu::llvmc::skeleton::branch * branch_a) :
value (branch_a)
{
}

mu::llvmc::skeleton::module::module () :
global (new (GC) mu::llvmc::skeleton::branch (nullptr)),
the_unit_value (global)
{
}

mu::llvmc::skeleton::loop::loop () :
argument_predicate_offset (~0)
{
}

void mu::llvmc::skeleton::loop::set_argument_predicate_offset ()
{
    assert (argument_predicate_offset == ~0);
    argument_predicate_offset = arguments.size ();
}

mu::llvmc::skeleton::loop_element::loop_element (mu::llvmc::skeleton::branch * branch_a, mu::llvmc::skeleton::loop * source_a) :
value (branch_a),
source (source_a)
{  
}

mu::llvmc::skeleton::loop_element_value::loop_element_value (mu::llvmc::skeleton::branch * branch_a, mu::llvmc::skeleton::loop * source_a, size_t index_a) :
loop_element (branch_a, source_a),
index (index_a)
{
}

mu::llvmc::skeleton::type * mu::llvmc::skeleton::loop_element_value::type ()
{
    assert (index < source->results.size ());
    auto result (source->results [index]->type ());
    return result;
}

mu::llvmc::skeleton::loop_element_unit::loop_element_unit (mu::llvmc::skeleton::branch * branch_a, mu::llvmc::skeleton::loop * source_a, size_t index_a) :
loop_element (branch_a, source_a),
index (index_a)
{
}

mu::llvmc::skeleton::type * mu::llvmc::skeleton::loop_element_unit::type ()
{
    return &the_unit_type;
}

mu::llvmc::skeleton::loop_parameter::loop_parameter (mu::llvmc::skeleton::branch * branch_a, mu::llvmc::skeleton::type * type_a) :
value (branch_a),
type_m (type_a)
{
}

mu::llvmc::skeleton::type * mu::llvmc::skeleton::loop_parameter::type ()
{
    return type_m;
}

mu::llvmc::skeleton::predicate::predicate (mu::llvmc::predicates type_a) :
type (type_a)
{
}

mu::llvmc::skeleton::asm_c::asm_c (mu::llvmc::skeleton::type * type_a, mu::string const & text_a, mu::string const & constraint_a) :
type_m (type_a),
text (text_a),
constraint (constraint_a)
{
}

mu::llvmc::skeleton::integer_type mu::llvmc::skeleton::integer_1_type (1);
mu::llvmc::skeleton::integer_type mu::llvmc::skeleton::integer_8_type (8);
mu::llvmc::skeleton::unit_type mu::llvmc::skeleton::the_unit_type;