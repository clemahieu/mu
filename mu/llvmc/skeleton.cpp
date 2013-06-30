#include <mu/llvmc/skeleton.hpp>

#include <mu/llvmc/analyzer.hpp>
#include <mu/core/error_string.hpp>
#include <mu/llvmc/skeleton_t.hpp>

#include <gc_cpp.h>

mu::llvmc::skeleton::constant_array::constant_array (mu::core::region const & region_a, mu::llvmc::skeleton::branch * branch_a, mu::llvmc::skeleton::array_type * type_a, mu::vector <mu::llvmc::skeleton::constant *> const & initializer_a) :
constant (region_a, branch_a),
type_m (type_a),
initializer (initializer_a)
{
    assert (initializer_a.size () == type_a->size);
}

mu::llvmc::skeleton::type * mu::llvmc::skeleton::constant_array::type ()
{
	return type_m;
}

mu::llvmc::skeleton::global_variable::global_variable (mu::core::region const & region_a, mu::llvmc::skeleton::branch * branch_a, mu::llvmc::skeleton::constant * initializer_a) :
constant (region_a, branch_a),
type_m (new (GC) mu::llvmc::skeleton::pointer_type (initializer_a->type ())),
initializer (initializer_a)
{	
}

mu::llvmc::skeleton::type * mu::llvmc::skeleton::global_variable::type ()
{
	return type_m;
}

void mu::llvmc::skeleton::function::add_branch_end ()
{
	branch_ends.push_back (results.size ());
}

void mu::llvmc::skeleton::function::add_predicate_offset ()
{
	predicate_offsets.push_back (results.size ());
}

void mu::llvmc::skeleton::function::set_predicate_offset ()
{
	predicate_offset = results.size ();
}

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

mu::llvmc::skeleton::switch_i::switch_i (mu::llvmc::skeleton::branch * branch_a, mu::vector <mu::llvmc::skeleton::node *> const & arguments_a, mu::llvmc::skeleton::unit_type * type_a) :
branch (branch_a),
arguments (arguments_a),
type_m (type_a)
{
}

mu::llvmc::skeleton::call_element::call_element (mu::core::region const & region_a, mu::llvmc::skeleton::branch * branch_a, mu::llvmc::skeleton::function_call * source_a, mu::llvmc::skeleton::type * type_a) :
value (region_a, branch_a),
source (source_a),
type_m (type_a)
{
}

mu::llvmc::skeleton::node::~node ()
{
}

mu::llvmc::skeleton::function::function (mu::core::region const & region_a, mu::llvmc::skeleton::branch * global_a) :
constant (region_a, global_a),
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

mu::llvmc::skeleton::value::value (mu::core::region const & region_a, mu::llvmc::skeleton::branch * branch_a) :
branch (branch_a),
region (region_a),
predicate (nullptr),
generated (nullptr)
{
}

mu::llvmc::skeleton::integer_type::integer_type (size_t bits_a) :
bits (bits_a)
{
}

mu::llvmc::skeleton::parameter::parameter (mu::core::region const & region_a, mu::llvmc::skeleton::branch * branch_a, mu::llvmc::skeleton::type * type_a, mu::string const & name_a) :
value (region_a, branch_a),
type_m (type_a),
name (name_a)
{
}

mu::llvmc::skeleton::result::result (mu::llvmc::skeleton::type * type_a, mu::llvmc::skeleton::value * value_a):
type (type_a),
value (value_a)
{
}

mu::llvmc::skeleton::instruction::instruction (mu::core::region const & region_a, mu::llvmc::skeleton::branch * branch_a, mu::vector <mu::llvmc::skeleton::node *> const & arguments_a, size_t predicate_position_a) :
value (region_a, branch_a),
arguments (arguments_a),
predicate_position (predicate_position_a),
type_m (get_type ())
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

mu::llvmc::skeleton::join_value::join_value (mu::core::region const & region_a, mu::llvmc::skeleton::branch * branch_a, mu::vector <mu::llvmc::skeleton::value *> const &arguments_a) :
value (region_a, branch_a),
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

mu::llvmc::skeleton::type * mu::llvmc::skeleton::call_element::type ()
{
    return type_m;
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

mu::llvmc::skeleton::function_call::function_call (mu::llvmc::skeleton::function * target_a, mu::llvmc::skeleton::branch * branch_a, mu::vector <mu::llvmc::skeleton::node *> const & arguments_a, size_t predicate_offset_a, mu::llvmc::skeleton::type * type_a):
target (target_a),
branch (branch_a),
arguments (arguments_a),
predicate_offset (predicate_offset_a),
type_m (type_a)
{
}

mu::llvmc::skeleton::switch_element::switch_element (mu::core::region const & region_a, mu::llvmc::skeleton::branch * branch_a, mu::llvmc::skeleton::switch_i * source_a, mu::llvmc::skeleton::constant_integer * value_a) :
value (region_a, branch_a),
source (source_a),
value_m (value_a)
{
    source_a->elements.push_back (this);
}

mu::llvmc::skeleton::constant::constant (mu::core::region const & region_a, mu::llvmc::skeleton::branch * branch_a) :
value (region_a, branch_a)
{
}

mu::llvmc::skeleton::constant_integer::constant_integer (mu::core::region const & region_a, mu::llvmc::skeleton::branch * branch_a, size_t bits_a, uint64_t value_a) :
constant (region_a, branch_a),
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

mu::llvmc::skeleton::constant_aggregate_zero::constant_aggregate_zero (mu::core::region const & region_a, mu::llvmc::skeleton::branch * branch_a, mu::llvmc::skeleton::type * type_a) :
constant (region_a, branch_a),
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
        result = *pointed_type == (*other_l->pointed_type);
    }
    return result;
}

mu::llvmc::skeleton::constant_pointer_null::constant_pointer_null (mu::core::region const & region_a, mu::llvmc::skeleton::branch * branch_a, mu::llvmc::skeleton::type * type_a) :
constant (region_a, branch_a),
type_m (type_a)
{
}

mu::llvmc::skeleton::type * mu::llvmc::skeleton::constant_pointer_null::type ()
{
    return type_m;
}

mu::llvmc::skeleton::type * mu::llvmc::skeleton::instruction::binary_integer_type ()
{
    mu::llvmc::skeleton::type * result;
    assert (predicate_position == 3);
    assert (dynamic_cast <mu::llvmc::skeleton::value *> (arguments [1]) != nullptr);
    assert (dynamic_cast <mu::llvmc::skeleton::value *> (arguments [2]) != nullptr);
    assert (*dynamic_cast <mu::llvmc::skeleton::value *> (arguments [1])->type () == *dynamic_cast <mu::llvmc::skeleton::value *> (arguments [2])->type ());
    result = static_cast <mu::llvmc::skeleton::value *> (arguments [1])->type ();
    return result;
}

mu::llvmc::skeleton::type * mu::llvmc::skeleton::instruction::type ()
{
    return type_m;
}

mu::llvmc::skeleton::type * mu::llvmc::skeleton::instruction::get_type ()
{
    mu::llvmc::skeleton::type * result (nullptr);
    switch (marker ())
    {
        case mu::llvmc::instruction_type::add:
        {
            result = binary_integer_type ();
            break;
        }
        case mu::llvmc::instruction_type::and_i:
        {
            result = binary_integer_type ();
            break;
        }
        case mu::llvmc::instruction_type::alloca:
        {
            assert (predicate_position == 2);
            assert (dynamic_cast <mu::llvmc::skeleton::type *> (arguments [1]) != nullptr);
            result = new (GC) mu::llvmc::skeleton::pointer_type (static_cast <mu::llvmc::skeleton::type *> (arguments [1]));
            
            break;
        }
        case mu::llvmc::instruction_type::ashr:
        {
            result = binary_integer_type ();
            break;
        }
        case mu::llvmc::instruction_type::bitcast:
        {
            assert (predicate_position == 3);
            assert (dynamic_cast <mu::llvmc::skeleton::type *> (arguments [2]) != nullptr);
            result = static_cast <mu::llvmc::skeleton::type *> (arguments [2]);
            break;
        }
        case mu::llvmc::instruction_type::cmpxchg:
        {
            assert (predicate_position == 4);
            assert (dynamic_cast <mu::llvmc::skeleton::value *> (arguments [1]) != nullptr);
            assert (dynamic_cast <mu::llvmc::skeleton::value *> (arguments [2]) != nullptr);
            assert (dynamic_cast <mu::llvmc::skeleton::value *> (arguments [3]) != nullptr);
            assert (*dynamic_cast <mu::llvmc::skeleton::value *> (arguments [2])->type () == *dynamic_cast <mu::llvmc::skeleton::value *> (arguments [3])->type ());
            result = static_cast <mu::llvmc::skeleton::value *> (arguments [2])->type ();
            break;
        }
		case mu::llvmc::instruction_type::getelementptr:
		{
            assert (predicate_position >= 3);
            assert (dynamic_cast <mu::llvmc::skeleton::value *> (arguments [1]) != nullptr);
            assert (dynamic_cast <mu::llvmc::skeleton::value *> (arguments [2]) != nullptr);
			auto value (static_cast <mu::llvmc::skeleton::value *> (arguments [1]));
			auto value_type (value->type ());
			assert (dynamic_cast <mu::llvmc::skeleton::pointer_type *> (value_type) != nullptr);
			value_type = static_cast <mu::llvmc::skeleton::pointer_type *> (value_type)->pointed_type;
			for (auto i (arguments.begin () + 3), j (arguments.begin () + predicate_position); i != j; ++i)
			{
				assert (dynamic_cast <mu::llvmc::skeleton::constant_integer *> (*i) != nullptr);
				auto index (static_cast <mu::llvmc::skeleton::constant_integer *> (*i));
				assert (dynamic_cast <mu::llvmc::skeleton::struct_type *> (value_type) != nullptr);
				assert (static_cast <mu::llvmc::skeleton::struct_type *> (value_type)->elements.size () > index->value_m);
				value_type = static_cast <mu::llvmc::skeleton::struct_type *> (value_type)->elements [index->value_m];
			}
            value_type = new (GC) mu::llvmc::skeleton::pointer_type (value_type);
			return value_type;
			break;
		}
        case mu::llvmc::instruction_type::icmp:
        {
            assert (false);
            break;
        }
        case mu::llvmc::instruction_type::inttoptr:
        {
            assert (predicate_position == 3);
            assert (dynamic_cast <mu::llvmc::skeleton::type *> (arguments [2]) != nullptr);
            result = static_cast <mu::llvmc::skeleton::type *> (arguments [2]);
            break;
        }
        case mu::llvmc::instruction_type::load:
        {
            assert (predicate_position == 2);
            assert (dynamic_cast <mu::llvmc::skeleton::value *> (arguments [1]) != nullptr);
            auto pointer_type (static_cast <mu::llvmc::skeleton::value *> (arguments [1])->type ());
            assert (dynamic_cast <mu::llvmc::skeleton::pointer_type *> (pointer_type) != nullptr);
            result = static_cast <mu::llvmc::skeleton::pointer_type *> (pointer_type)->pointed_type;
            break;
        }
        case mu::llvmc::instruction_type::lshr:
        {
            result = binary_integer_type ();
            break;
        }
        case mu::llvmc::instruction_type::mul:
        {
            result = binary_integer_type ();
            break;
        }
        case mu::llvmc::instruction_type::or_i:
        {
            result = binary_integer_type ();
            break;
        }
        case mu::llvmc::instruction_type::ptrtoint:
        {
            assert (predicate_position == 3);
            assert (dynamic_cast <mu::llvmc::skeleton::type *> (arguments [2]) != nullptr);
            result = static_cast <mu::llvmc::skeleton::type *> (arguments [2]);
            break;
        }
        case mu::llvmc::instruction_type::sdiv:
        {
            result = binary_integer_type ();
            break;
        }
        case mu::llvmc::instruction_type::sext:
        {
            assert (predicate_position == 3);
            assert (dynamic_cast <mu::llvmc::skeleton::value *> (arguments [1]) != nullptr);
            assert (dynamic_cast <mu::llvmc::skeleton::type *> (arguments [2]) != nullptr);
            result = static_cast <mu::llvmc::skeleton::type *> (arguments [2]);
            break;
        }
        case mu::llvmc::instruction_type::shl:
        {
            result = binary_integer_type ();
            break;
        }
        case mu::llvmc::instruction_type::srem:
        {
            result = binary_integer_type ();
            break;
        }
        case mu::llvmc::instruction_type::store:
        {
            assert (false);
            break;
        }
        case mu::llvmc::instruction_type::sub:
        {
            result = binary_integer_type ();
            break;
        }
        case mu::llvmc::instruction_type::udiv:
        {
            result = binary_integer_type ();
            break;
        }
        case mu::llvmc::instruction_type::urem:
        {
            result = binary_integer_type ();
            break;
        }
        case mu::llvmc::instruction_type::xor_i:
        {
            result = binary_integer_type ();
            break;
        }
        case mu::llvmc::instruction_type::zext:
        {
            assert (predicate_position == 3);
            assert (dynamic_cast <mu::llvmc::skeleton::value *> (arguments [1]) != nullptr);
            assert (dynamic_cast <mu::llvmc::skeleton::type *> (arguments [2]) != nullptr);
            result = static_cast <mu::llvmc::skeleton::type *> (arguments [2]);
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
    return source->type_m;
}

mu::llvmc::skeleton::type * mu::llvmc::skeleton::unit_value::type ()
{
    return type_m;
}

mu::llvmc::skeleton::unit_value::unit_value (mu::llvmc::skeleton::branch * branch_a, mu::llvmc::skeleton::type * type_a) :
value (mu::empty_region, branch_a),
type_m (type_a)
{
}

mu::llvmc::skeleton::module::module () :
global (new (GC) mu::llvmc::skeleton::branch (nullptr)),
integer_1_type (1),
integer_8_type (8),
the_unit_value (global, &the_unit_type)
{
}

mu::llvmc::skeleton::loop::loop (mu::llvmc::skeleton::type * type_a) :
argument_predicate_offset (~0),
type_m (type_a)
{
}

void mu::llvmc::skeleton::loop::set_argument_predicate_offset ()
{
    assert (argument_predicate_offset == ~0);
    argument_predicate_offset = arguments.size ();
}

mu::llvmc::skeleton::loop_element::loop_element (mu::core::region const & region_a, mu::llvmc::skeleton::branch * branch_a, mu::llvmc::skeleton::loop * source_a, mu::llvmc::skeleton::type * type_a) :
value (region_a, branch_a),
source (source_a),
type_m (type_a)
{  
}

mu::llvmc::skeleton::type * mu::llvmc::skeleton::loop_element::type ()
{
    return type_m;
}

mu::llvmc::skeleton::loop_parameter::loop_parameter (mu::core::region const & region_a, mu::llvmc::skeleton::branch * branch_a, mu::llvmc::skeleton::type * type_a) :
value (region_a, branch_a),
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

mu::llvmc::skeleton::inline_asm::inline_asm (mu::core::region const & region_a, mu::llvmc::skeleton::branch * branch_a, mu::vector <mu::llvmc::skeleton::node *> const & arguments_a, size_t predicate_position_a) :
value (region_a, branch_a),
arguments (arguments_a),
predicate_position (predicate_position_a)
{
}

mu::llvmc::skeleton::type * mu::llvmc::skeleton::inline_asm::type ()
{
	assert (arguments.size () > 0);
	assert (dynamic_cast <mu::llvmc::skeleton::asm_c *> (arguments [0]) != nullptr);
	auto asm_l (static_cast <mu::llvmc::skeleton::asm_c *> (arguments [0]));
	return asm_l->type_m;
}

mu::llvmc::skeleton::named::named (mu::core::region const & region_a, mu::llvmc::skeleton::value * value_a, mu::string const & name_a) :
value (region_a, value_a->branch),
value_m (value_a),
name (name_a)
{
}

mu::llvmc::skeleton::type * mu::llvmc::skeleton::named::type ()
{
    auto result (value_m->type ());
    return result;
}

mu::llvmc::skeleton::identity_element::identity_element (mu::llvmc::skeleton::branch * branch_a, mu::llvmc::skeleton::identity_call * source_a) :
value (mu::empty_region, branch_a),
source (source_a)
{
}

mu::llvmc::skeleton::identity_element_value::identity_element_value (mu::llvmc::skeleton::branch * branch_a, mu::llvmc::skeleton::identity_call * source_a, size_t index_a) :
identity_element (branch_a, source_a),
index (index_a)
{
}

mu::llvmc::skeleton::type * mu::llvmc::skeleton::identity_element_value::type ()
{
    assert (source->arguments.size () > index);
    assert (dynamic_cast <mu::llvmc::skeleton::value *> (source->arguments [index]) != nullptr);
    auto result (static_cast <mu::llvmc::skeleton::value *> (source->arguments [index])->type ());
    return result;
}

mu::llvmc::skeleton::identity_element_unit::identity_element_unit (mu::llvmc::skeleton::branch * branch_a, mu::llvmc::skeleton::identity_call * source_a) :
identity_element (branch_a, source_a)
{
}

mu::llvmc::skeleton::type * mu::llvmc::skeleton::identity_element_unit::type ()
{
    return source->type_m;
}

mu::llvmc::skeleton::identity_call::identity_call (mu::vector <mu::llvmc::skeleton::node *> const & arguments_a, size_t predicate_offset_a, mu::llvmc::skeleton::type * type_a) :
arguments (arguments_a),
predicate_offset (predicate_offset_a),
type_m (type_a)
{
}

mu::llvmc::skeleton::array_type::array_type (mu::llvmc::skeleton::type * element_a, size_t size_a) :
element (element_a),
size (size_a)
{
}

bool mu::llvmc::skeleton::array_type::operator == (mu::llvmc::skeleton::type const & other_a) const
{
    auto result (false);
    auto array_type_l (dynamic_cast <mu::llvmc::skeleton::array_type const *> (&other_a));
    if (array_type_l != nullptr)
    {
        result = *element == *array_type_l->element && size == array_type_l->size;
    }
    return result;
}

void mu::llvmc::skeleton::node::visit (mu::llvmc::skeleton::visitor * visitor_a)
{
    visitor_a->node (this);
}

void mu::llvmc::skeleton::array_type::visit (mu::llvmc::skeleton::visitor * visitor_a)
{
    visitor_a->array_type (this);
}

void mu::llvmc::skeleton::inline_asm::visit (mu::llvmc::skeleton::visitor * visitor_a)
{
    visitor_a->inline_asm (this);
}

void mu::llvmc::skeleton::join_value::visit (mu::llvmc::skeleton::visitor * visitor_a)
{
    visitor_a->join_value (this);
}

void mu::llvmc::skeleton::unit_value::visit (mu::llvmc::skeleton::visitor * visitor_a)
{
    visitor_a->unit_value (this);
}

void mu::llvmc::skeleton::instruction::visit (mu::llvmc::skeleton::visitor * visitor_a)
{
    visitor_a->instruction (this);
}

void mu::llvmc::skeleton::struct_type::visit (mu::llvmc::skeleton::visitor * visitor_a)
{
    visitor_a->struct_type (this);
}

void mu::llvmc::skeleton::call_element::visit (mu::llvmc::skeleton::visitor * visitor_a)
{
    visitor_a->call_element (this);
}

void mu::llvmc::skeleton::integer_type::visit (mu::llvmc::skeleton::visitor * visitor_a)
{
    visitor_a->integer_type (this);
}

void mu::llvmc::skeleton::loop_element::visit (mu::llvmc::skeleton::visitor * visitor_a)
{
    visitor_a->loop_element (this);
}

void mu::llvmc::skeleton::pointer_type::visit (mu::llvmc::skeleton::visitor * visitor_a)
{
    visitor_a->pointer_type (this);
}

void mu::llvmc::skeleton::function_type::visit (mu::llvmc::skeleton::visitor * visitor_a)
{
    visitor_a->function_type (this);
}

void mu::llvmc::skeleton::constant_array::visit (mu::llvmc::skeleton::visitor * visitor_a)
{
    visitor_a->constant_array (this);
}

void mu::llvmc::skeleton::loop_parameter::visit (mu::llvmc::skeleton::visitor * visitor_a)
{
    visitor_a->loop_parameter (this);
}

void mu::llvmc::skeleton::switch_element::visit (mu::llvmc::skeleton::visitor * visitor_a)
{
    visitor_a->switch_element (this);
}

void mu::llvmc::skeleton::global_variable::visit (mu::llvmc::skeleton::visitor * visitor_a)
{
    visitor_a->global_variable (this);
}

void mu::llvmc::skeleton::constant_integer::visit (mu::llvmc::skeleton::visitor * visitor_a)
{
    visitor_a->constant_integer (this);
}

void mu::llvmc::skeleton::constant_pointer_null::visit (mu::llvmc::skeleton::visitor * visitor_a)
{
    visitor_a->constant_pointer_null (this);
}

void mu::llvmc::skeleton::identity_element_value::visit (mu::llvmc::skeleton::visitor * visitor_a)
{
    visitor_a->identity_element_value (this);
}

void mu::llvmc::skeleton::constant_aggregate_zero::visit (mu::llvmc::skeleton::visitor * visitor_a)
{
    visitor_a->constant_aggregate_zero (this);
}

void mu::llvmc::skeleton::join::visit (mu::llvmc::skeleton::visitor * visitor_a)
{
    visitor_a->join (this);
}

void mu::llvmc::skeleton::type::visit (mu::llvmc::skeleton::visitor * visitor_a)
{
    visitor_a->type (this);
}

void mu::llvmc::skeleton::asm_c::visit (mu::llvmc::skeleton::visitor * visitor_a)
{
    visitor_a->asm_c (this);
}

void mu::llvmc::skeleton::named::visit (mu::llvmc::skeleton::visitor * visitor_a)
{
    visitor_a->named (this);
}

void mu::llvmc::skeleton::value::visit (mu::llvmc::skeleton::visitor * visitor_a)
{
    visitor_a->value (this);
}

void mu::llvmc::skeleton::marker::visit (mu::llvmc::skeleton::visitor * visitor_a)
{
    visitor_a->marker (this);
}

void mu::llvmc::skeleton::result::visit (mu::llvmc::skeleton::visitor * visitor_a)
{
    visitor_a->result (this);
}

void mu::llvmc::skeleton::constant::visit (mu::llvmc::skeleton::visitor * visitor_a)
{
    visitor_a->constant (this);
}

void mu::llvmc::skeleton::function::visit (mu::llvmc::skeleton::visitor * visitor_a)
{
    visitor_a->function (this);
}

void mu::llvmc::skeleton::identity::visit (mu::llvmc::skeleton::visitor * visitor_a)
{
    visitor_a->identity (this);
}

void mu::llvmc::skeleton::parameter::visit (mu::llvmc::skeleton::visitor * visitor_a)
{
    visitor_a->parameter (this);
}

void mu::llvmc::skeleton::predicate::visit (mu::llvmc::skeleton::visitor * visitor_a)
{
    visitor_a->predicate (this);
}

void mu::llvmc::skeleton::unit_type::visit (mu::llvmc::skeleton::visitor * visitor_a)
{
    visitor_a->unit_type (this);
}

void mu::llvmc::skeleton::identity_element::visit (mu::llvmc::skeleton::visitor * visitor_a)
{
    visitor_a->identity_element (this);
}

void mu::llvmc::skeleton::identity_element_unit::visit (mu::llvmc::skeleton::visitor * visitor_a)
{
    visitor_a->identity_element_unit (this);
}

void mu::llvmc::skeleton::visitor::unexpected (mu::llvmc::skeleton::node * node_a)
{
    assert (false && "Unexpected node");
}

void mu::llvmc::skeleton::visitor::node (mu::llvmc::skeleton::node * node_a)
{
    unexpected (node_a);
}

void mu::llvmc::skeleton::visitor::array_type (mu::llvmc::skeleton::array_type * node_a)
{
    type (node_a);
}

void mu::llvmc::skeleton::visitor::inline_asm (mu::llvmc::skeleton::inline_asm * node_a)
{
    value (node_a);
}

void mu::llvmc::skeleton::visitor::join_value (mu::llvmc::skeleton::join_value * node_a)
{
    value (node_a);
}

void mu::llvmc::skeleton::visitor::unit_value (mu::llvmc::skeleton::unit_value * node_a)
{
    value (node_a);
}

void mu::llvmc::skeleton::visitor::instruction (mu::llvmc::skeleton::instruction * node_a)
{
    value (node_a);
}

void mu::llvmc::skeleton::visitor::struct_type (mu::llvmc::skeleton::struct_type * node_a)
{
    type (node_a);
}

void mu::llvmc::skeleton::visitor::call_element (mu::llvmc::skeleton::call_element * node_a)
{
    value (node_a);
}

void mu::llvmc::skeleton::visitor::integer_type (mu::llvmc::skeleton::integer_type * node_a)
{
    type (node_a);
}

void mu::llvmc::skeleton::visitor::loop_element (mu::llvmc::skeleton::loop_element * node_a)
{
    value (node_a);
}

void mu::llvmc::skeleton::visitor::pointer_type (mu::llvmc::skeleton::pointer_type * node_a)
{
    type (node_a);
}

void mu::llvmc::skeleton::visitor::function_type (mu::llvmc::skeleton::function_type * node_a)
{
    type (node_a);
}

void mu::llvmc::skeleton::visitor::constant_array (mu::llvmc::skeleton::constant_array * node_a)
{
    constant (node_a);
}

void mu::llvmc::skeleton::visitor::loop_parameter (mu::llvmc::skeleton::loop_parameter * node_a)
{
    value (node_a);
}

void mu::llvmc::skeleton::visitor::switch_element (mu::llvmc::skeleton::switch_element * node_a)
{
    value (node_a);
}

void mu::llvmc::skeleton::visitor::global_variable (mu::llvmc::skeleton::global_variable * node_a)
{
    constant (node_a);
}

void mu::llvmc::skeleton::visitor::constant_integer (mu::llvmc::skeleton::constant_integer * node_a)
{
    constant (node_a);
}

void mu::llvmc::skeleton::visitor::constant_pointer_null (mu::llvmc::skeleton::constant_pointer_null * node_a)
{
    constant (node_a);
}

void mu::llvmc::skeleton::visitor::identity_element_value (mu::llvmc::skeleton::identity_element_value * node_a)
{
    identity_element (node_a);
}

void mu::llvmc::skeleton::visitor::constant_aggregate_zero (mu::llvmc::skeleton::constant_aggregate_zero * node_a)
{
    constant (node_a);
}

void mu::llvmc::skeleton::visitor::join (mu::llvmc::skeleton::join * node_a)
{
    node (node_a);
}

void mu::llvmc::skeleton::visitor::type (mu::llvmc::skeleton::type * node_a)
{
    node (node_a);
}

void mu::llvmc::skeleton::visitor::asm_c (mu::llvmc::skeleton::asm_c * node_a)
{
    node (node_a);
}

void mu::llvmc::skeleton::visitor::named (mu::llvmc::skeleton::named * node_a)
{
    value (node_a);
}

void mu::llvmc::skeleton::visitor::value (mu::llvmc::skeleton::value * node_a)
{
    node (node_a);
}

void mu::llvmc::skeleton::visitor::marker (mu::llvmc::skeleton::marker * node_a)
{
    node (node_a);
}

void mu::llvmc::skeleton::visitor::result (mu::llvmc::skeleton::result * node_a)
{
    node (node_a);
}

void mu::llvmc::skeleton::visitor::constant (mu::llvmc::skeleton::constant * node_a)
{
    value (node_a);
}

void mu::llvmc::skeleton::visitor::function (mu::llvmc::skeleton::function * node_a)
{
    constant (node_a);
}

void mu::llvmc::skeleton::visitor::identity (mu::llvmc::skeleton::identity * node_a)
{
    node (node_a);
}

void mu::llvmc::skeleton::visitor::parameter (mu::llvmc::skeleton::parameter * node_a)
{
    value (node_a);
}

void mu::llvmc::skeleton::visitor::predicate (mu::llvmc::skeleton::predicate * node_a)
{
    node (node_a);
}

void mu::llvmc::skeleton::visitor::unit_type (mu::llvmc::skeleton::unit_type * node_a)
{
    type (node_a);
}

void mu::llvmc::skeleton::visitor::identity_element (mu::llvmc::skeleton::identity_element * node_a)
{
    value (node_a);
}

void mu::llvmc::skeleton::visitor::identity_element_unit (mu::llvmc::skeleton::identity_element_unit * node_a)
{
    identity_element (node_a);
}

mu::llvmc::skeleton::icmp::icmp (mu::core::region const & region_a, mu::llvmc::skeleton::branch * branch_a, mu::llvmc::skeleton::type * type_a, mu::llvmc::skeleton::predicate * predicate_a, mu::llvmc::skeleton::value * left_a, mu::llvmc::skeleton::value * right_a) :
value (region_a, branch_a),
type_m (type_a),
predicate_m (predicate_a),
left (left_a),
right (right_a)
{
}

void mu::llvmc::skeleton::icmp::visit (mu::llvmc::skeleton::visitor * visitor_a)
{
    visitor_a->icmp (this);
}

mu::llvmc::skeleton::type * mu::llvmc::skeleton::icmp::type ()
{
    return type_m;
}

void mu::llvmc::skeleton::visitor::icmp (mu::llvmc::skeleton::icmp * node_a)
{
    value (node_a);
}

mu::llvmc::skeleton::store::store (mu::core::region const & region_a, mu::llvmc::skeleton::branch * branch_a, mu::llvmc::skeleton::type * type_a, mu::llvmc::skeleton::value * source_a, mu::llvmc::skeleton::value * destination_a) :
value (region_a, branch_a),
type_m (type_a),
source (source_a),
destination (destination_a)
{
}

void mu::llvmc::skeleton::store::visit (mu::llvmc::skeleton::visitor * visitor_a)
{
    visitor_a->store (this);
}

mu::llvmc::skeleton::type * mu::llvmc::skeleton::store::type ()
{
    return type_m;
}

void mu::llvmc::skeleton::visitor::store (mu::llvmc::skeleton::store * node_a)
{
    value (node_a);
}

mu::llvmc::skeleton::type::type () :
generated (nullptr),
debug (nullptr)
{
}