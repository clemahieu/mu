#include <mu/llvmc/skeleton.hpp>

#include <mu/llvmc/analyzer.hpp>
#include <mu/core/error_string.hpp>
#include <mu/llvmc/skeleton_t.hpp>

#include <gc_cpp.h>

static mu::llvmc::skeleton::factory b;
mu::llvmc::skeleton::branch mu::llvmc::skeleton::branch::global = mu::llvmc::skeleton::branch (nullptr);

mu::llvmc::skeleton::constant_array::constant_array (mu::core::region const & region_a, mu::llvmc::skeleton::fixed_array_type * type_a, mu::vector <mu::llvmc::skeleton::constant *> const & initializer_a) :
constant (region_a),
type_m (type_a),
initializer (initializer_a)
{
    assert (initializer_a.size () == type_a->size);
}

mu::llvmc::skeleton::type * mu::llvmc::skeleton::constant_array::type ()
{
	return type_m;
}

mu::llvmc::skeleton::global_variable::global_variable (mu::core::region const & region_a, mu::llvmc::skeleton::constant * initializer_a) :
global_value (region_a),
type_m (new (GC) mu::llvmc::skeleton::pointer_type (initializer_a->type ())),
initializer (initializer_a)
{	
}

mu::llvmc::skeleton::type * mu::llvmc::skeleton::global_variable::type ()
{
	return type_m;
}

void mu::llvmc::skeleton::function::empty_node (mu::llvmc::skeleton::node *, size_t)
{
}

bool mu::llvmc::skeleton::function::empty_loop_predicate ()
{
    return true;
}

mu::llvmc::skeleton::loop_branch & mu::llvmc::skeleton::loop::add_branch ()
{
    results.push_back (decltype (results)::value_type ());
    return results.back ();
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

mu::llvmc::skeleton::function::function (mu::core::region const & region_a) :
global_value (region_a),
type_m (this),
pointer_type_m (&type_m),
entry (new (GC) mu::llvmc::skeleton::branch (&mu::llvmc::skeleton::branch::global))
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

mu::llvmc::skeleton::type * mu::llvmc::skeleton::function::type ()
{
    return & pointer_type_m;
}

mu::llvmc::skeleton::pointer_type::pointer_type (mu::llvmc::skeleton::type * type_a):
pointed_type (type_a)
{
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

bool mu::llvmc::skeleton::function_type::parameters_equal (mu::llvmc::skeleton::function_type const & other_a) const
{
    auto result (function->parameters.size () == other_a.function->parameters.size ());
    for (auto i (function->parameters.begin ()), j (function->parameters.end ()), k (other_a.function->parameters.begin ()); result && i != j; ++i, ++k)
    {
        result = *(*i)->type () == *(*k)->type ();
    }
    return result;
}

bool mu::llvmc::skeleton::function_type::results_equal (mu::llvmc::skeleton::function_type const & other_a) const
{
    auto result (function->results.size () == other_a.function->results.size ());
    for (auto i (function->results.branches.begin ()), j (function->results.branches.end ()), k (other_a.function->results.branches.begin ()); result && i != j; ++i, ++k)
    {
        result = i->results.size () == k->results.size ();
        for (auto l (i->results.begin ()), m (i->results.end ()), n (k->results.begin ()); result && l != m; ++l, ++n)
        {
            result = *(*l)->type == *(*n)->type;
        }
    }
    return result;
}

bool mu::llvmc::skeleton::function_type::operator == (mu::llvmc::skeleton::type const & other_a) const
{
    auto result (false);
    auto other_function (dynamic_cast <mu::llvmc::skeleton::function_type const *> (&other_a));
    if (other_function != nullptr)
    {
        result = parameters_equal (*other_function) && results_equal (*other_function);
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
    for (auto i (results.branches.begin ()), j (results.branches.end ()); llvm_values < 2 && i != j; ++i)
    {
        for (auto k (i->results.begin ()), l (i->results.end ()); llvm_values < 2 && k != l; ++k)
        {
            if (!(*k)->type->is_unit_type ())
            {
                ++llvm_values;
            }
        }
    }
    switch (results.size ())
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

mu::llvmc::skeleton::constant::constant (mu::core::region const & region_a) :
value (region_a, &mu::llvmc::skeleton::branch::global)
{
}

mu::llvmc::skeleton::constant_integer::constant_integer (mu::core::region const & region_a, mu::llvmc::skeleton::integer_type * type_a, uint64_t value_a) :
constant (region_a),
type_m (type_a),
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

mu::llvmc::skeleton::constant_aggregate_zero::constant_aggregate_zero (mu::core::region const & region_a, mu::llvmc::skeleton::type * type_a) :
constant (region_a),
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

mu::llvmc::skeleton::constant_pointer_null::constant_pointer_null (mu::core::region const & region_a, mu::llvmc::skeleton::type * type_a) :
constant (region_a),
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
        case mu::llvmc::instruction_type::extractvalue:
        {
            assert (predicate_position == 3);
            auto aggregate (mu::cast <mu::llvmc::skeleton::value> (arguments [1]));
            auto type (mu::cast <mu::llvmc::skeleton::struct_type> (aggregate->type ()));
            auto index (mu::cast <mu::llvmc::skeleton::constant_integer> (arguments [2]));
            assert (index->value_m < type->elements.size ());
            result = type->elements [index->value_m];
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
		case mu::llvmc::instruction_type::insertvalue:
		{
			assert (predicate_position >= 4);
			auto struct_l (mu::cast <mu::llvmc::skeleton::value> (arguments [1]));
			assert (dynamic_cast <mu::llvmc::skeleton::struct_type *> (struct_l->type ()));
			result = struct_l->type ();
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
		case mu::llvmc::instruction_type::select:
		{
			assert (predicate_position == 4);
			result = mu::cast <mu::llvmc::skeleton::value> (arguments [2])->type ();
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
            result = mu::cast <mu::llvmc::skeleton::type> (arguments [2]);
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

mu::llvmc::skeleton::type * mu::llvmc::skeleton::join_element::type ()
{
    return type_m;
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
entry (nullptr),
integer_1_type (1),
integer_8_type (8),
integer_32_type (32),
the_unit_value (&mu::llvmc::skeleton::branch::global, &the_unit_type),
single_reference (&integer_8_type),
double_reference ({&single_reference, &single_reference})
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

mu::llvmc::skeleton::loop_parameter::loop_parameter (mu::core::region const & region_a, mu::llvmc::skeleton::branch * branch_a, mu::llvmc::skeleton::type * type_a, mu::string const & name_a) :
value (region_a, branch_a),
type_m (type_a),
name (name_a)
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

mu::llvmc::skeleton::identity_element::identity_element (mu::llvmc::skeleton::branch * branch_a, mu::llvmc::skeleton::identity_call * source_a, mu::llvmc::skeleton::type * type_a) :
value (mu::empty_region, branch_a),
source (source_a),
type_m (type_a)
{
}

mu::llvmc::skeleton::type * mu::llvmc::skeleton::identity_element::type ()
{
    return type_m;
}

mu::llvmc::skeleton::identity_call::identity_call (mu::vector <mu::llvmc::skeleton::node *> const & arguments_a, size_t predicate_offset_a, mu::llvmc::skeleton::type * type_a) :
arguments (arguments_a),
predicate_offset (predicate_offset_a),
type_m (type_a)
{
}

mu::llvmc::skeleton::fixed_array_type::fixed_array_type (mu::llvmc::skeleton::type * element_a, size_t size_a) :
element (element_a),
size (size_a)
{
}

bool mu::llvmc::skeleton::fixed_array_type::operator == (mu::llvmc::skeleton::type const & other_a) const
{
    auto result (false);
    auto array_type_l (dynamic_cast <mu::llvmc::skeleton::fixed_array_type const *> (&other_a));
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

void mu::llvmc::skeleton::fixed_array_type::visit (mu::llvmc::skeleton::visitor * visitor_a)
{
    visitor_a->fixed_array_type (this);
}

void mu::llvmc::skeleton::inline_asm::visit (mu::llvmc::skeleton::visitor * visitor_a)
{
    visitor_a->inline_asm (this);
}

void mu::llvmc::skeleton::join_element::visit (mu::llvmc::skeleton::visitor * visitor_a)
{
    visitor_a->join_element (this);
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

void mu::llvmc::skeleton::constant_aggregate_zero::visit (mu::llvmc::skeleton::visitor * visitor_a)
{
    visitor_a->constant_aggregate_zero (this);
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

void mu::llvmc::skeleton::visitor::unexpected (mu::llvmc::skeleton::node * node_a)
{
    assert (false && "Unexpected node");
}

void mu::llvmc::skeleton::visitor::number (mu::llvmc::skeleton::number * node_a)
{
	node (node_a);
}

void mu::llvmc::skeleton::visitor::node (mu::llvmc::skeleton::node * node_a)
{
    unexpected (node_a);
}

void mu::llvmc::skeleton::visitor::fixed_array_type (mu::llvmc::skeleton::fixed_array_type * node_a)
{
    type (node_a);
}

void mu::llvmc::skeleton::visitor::inline_asm (mu::llvmc::skeleton::inline_asm * node_a)
{
    value (node_a);
}

void mu::llvmc::skeleton::visitor::join_element (mu::llvmc::skeleton::join_element * node_a)
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
    global_value (node_a);
}

void mu::llvmc::skeleton::visitor::constant_integer (mu::llvmc::skeleton::constant_integer * node_a)
{
    constant (node_a);
}

void mu::llvmc::skeleton::visitor::constant_pointer_null (mu::llvmc::skeleton::constant_pointer_null * node_a)
{
    constant (node_a);
}

void mu::llvmc::skeleton::visitor::constant_aggregate_zero (mu::llvmc::skeleton::constant_aggregate_zero * node_a)
{
    constant (node_a);
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
    global_value (node_a);
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

void mu::llvmc::skeleton::visitor::sequence (mu::llvmc::skeleton::sequence * node_a)
{
    node (node_a);
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

mu::llvmc::skeleton::join_element::join_element (mu::core::region const & region_a, mu::llvmc::skeleton::branch * branch_a, mu::llvmc::skeleton::join_value * source_a, mu::llvmc::skeleton::type * type_a) :
value (region_a, branch_a),
source (source_a),
type_m (type_a)
{
}

mu::llvmc::skeleton::join_branch & mu::llvmc::skeleton::join_value::add_branch ()
{
    branches.push_back (decltype (branches)::value_type ());
    auto & result (branches [branches.size () - 1]);
    return result;
}

mu::llvmc::skeleton::join_branch::join_branch () :
predicate (nullptr)
{
}

bool mu::llvmc::skeleton::struct_type::operator == (mu::llvmc::skeleton::type const & other_a) const
{
    auto result (false);
    auto other_l (dynamic_cast <mu::llvmc::skeleton::struct_type const *> (&other_a));
    if (other_l != nullptr)
    {
        result = elements.size () == other_l->elements.size ();
        if (result)
        {
            for (auto i (elements.begin ()), j (elements.end ()), k (other_l->elements.begin ()); i != j && result; ++i, ++k)
            {
                result = *(*i) == *(*k);
            }
        }
    }
    return result;
}

void mu::llvmc::skeleton::undefined::visit (mu::llvmc::skeleton::visitor * visitor_a)
{
	visitor_a->undefined (this);
}

mu::llvmc::skeleton::type * mu::llvmc::skeleton::undefined::type ()
{
	return type_m;
}

void mu::llvmc::skeleton::visitor::undefined (mu::llvmc::skeleton::undefined * node_a)
{
	value (node_a);
}

void mu::llvmc::skeleton::template_c::visit (mu::llvmc::skeleton::visitor * visitor_a)
{
    visitor_a->template_c (this);
}

void mu::llvmc::skeleton::visitor::template_c (mu::llvmc::skeleton::template_c * node_a)
{
    node (node_a);
}

mu::llvmc::skeleton::undefined::undefined (mu::core::region const & region_a, mu::llvmc::skeleton::branch * branch_a, mu::llvmc::skeleton::type * type_a) :
value (region_a, branch_a),
type_m (type_a)
{
}

mu::llvmc::skeleton::global_value::global_value (mu::core::region const & region_a) :
constant (region_a)
{
}

void mu::llvmc::skeleton::global_value::visit (mu::llvmc::skeleton::visitor * visitor_a)
{
    visitor_a->global_value (this);
}

void mu::llvmc::skeleton::visitor::global_value (mu::llvmc::skeleton::global_value * node_a)
{
    constant (node_a);
}

mu::llvmc::skeleton::template_c::template_c (mu::llvmc::template_context * base_a) :
base (base_a)
{
    assert (base_a != nullptr);
}

void mu::llvmc::skeleton::node::named (mu::llvmc::skeleton::namespace_visitor * naming_a)
{
	naming_a->unnamed ();
}

void mu::llvmc::skeleton::module::named (mu::llvmc::skeleton::namespace_visitor * visitor_a)
{
    visitor_a->named (this);
}

void mu::llvmc::skeleton::module::visit (mu::llvmc::skeleton::visitor * visitor_a)
{
	visitor_a->module (this);
}

mu::llvmc::skeleton::node * mu::llvmc::skeleton::module::operator [] (mu::string const & name_a)
{
	auto existing (names.find (name_a));
	auto result (existing != names.end () ? existing->second : nullptr);
	return result;
}

void mu::llvmc::skeleton::visitor::module (mu::llvmc::skeleton::module * node_a)
{
	node (node_a);
}

void mu::llvmc::skeleton::constant_int_c::visit (mu::llvmc::skeleton::visitor * visitor_a)
{
	visitor_a->constant_int_c (this);
}

void mu::llvmc::skeleton::visitor::constant_int_c (mu::llvmc::skeleton::constant_int_c * node_a)
{
	node (node_a);
}

mu::llvmc::skeleton::node * mu::llvmc::skeleton::struct_type::operator [] (mu::string const & name_a)
{
	mu::llvmc::skeleton::node * result;
	auto existing (names.find (name_a));
	if (existing != names.end ())
	{
		result = existing->second;
	}
	else
	{
		result = nullptr;
	}
	return result;
}

void mu::llvmc::skeleton::struct_type::named (mu::llvmc::skeleton::namespace_visitor * naming_a)
{
	naming_a->named (this);
}

mu::llvmc::skeleton::value * mu::llvmc::skeleton::value::adapt (mu::llvmc::skeleton::type * target_type_a, mu::llvmc::function_processor & function_a, std::function <mu::core::error * (mu::core::region const &)> error_action_a)
{
	mu::llvmc::skeleton::value * result;
	if (*type () == *target_type_a)
	{
		result = this;
	}
	else
	{
		auto lhs_integer_type (dynamic_cast <mu::llvmc::skeleton::integer_type *> (type ()));
		auto rhs_integer_type (dynamic_cast <mu::llvmc::skeleton::integer_type *> (target_type_a));
		if (lhs_integer_type != nullptr && rhs_integer_type != nullptr)
		{
			assert (lhs_integer_type->bits != rhs_integer_type->bits);
			if (lhs_integer_type->bits < rhs_integer_type->bits)
			{
				result = b.instruction (region, branch, {b.marker (mu::llvmc::instruction_type::zext), this, rhs_integer_type}, {});
			}
			else
			{
				function_a.module_m.global_m.error = error_action_a (region);
				result = nullptr;
			}
		}
		else
		{
			function_a.module_m.global_m.error = error_action_a (region);
			result = nullptr;
		}
	}
	return result;
}

mu::llvmc::skeleton::value * mu::llvmc::skeleton::node::adapt_result (mu::llvmc::skeleton::type * target_type_a, mu::llvmc::function_processor & function_a, std::function <mu::core::error * (mu::core::region const &)> error_action_a)
{
    return adapt (target_type_a, function_a, error_action_a);
}

mu::llvmc::skeleton::fixed_array_type * mu::llvmc::skeleton::factory::fixed_array_type (mu::llvmc::skeleton::type * element_a, size_t size_a)
{
	return new (GC) mu::llvmc::skeleton::fixed_array_type (element_a, size_a);
}

mu::llvmc::skeleton::inline_asm * mu::llvmc::skeleton::factory::inline_asm (mu::core::region const & region_a, mu::llvmc::skeleton::branch * branch_a, mu::vector <mu::llvmc::skeleton::node *> const & arguments_a, size_t predicate_position_a)
{
	return new (GC) mu::llvmc::skeleton::inline_asm (region_a, branch_a, arguments_a, predicate_position_a);
}

mu::llvmc::skeleton::join_element * mu::llvmc::skeleton::factory::join_element (mu::core::region const & region_a, mu::llvmc::skeleton::branch * branch_a, mu::llvmc::skeleton::join_value * source_a, mu::llvmc::skeleton::type * type_a)
{
	return new (GC) mu::llvmc::skeleton::join_element (region_a, branch_a, source_a, type_a);
}

mu::llvmc::skeleton::unit_value * mu::llvmc::skeleton::factory::unit_value (mu::llvmc::skeleton::branch * branch_a, mu::llvmc::skeleton::type * type_a)
{
	return new (GC) mu::llvmc::skeleton::unit_value (branch_a, type_a);
}

mu::llvmc::skeleton::instruction * mu::llvmc::skeleton::factory::instruction (mu::core::region const & region_a, mu::llvmc::skeleton::branch * branch_a, mu::vector <mu::llvmc::skeleton::node *> const & arguments_a, size_t predicate_position_a)
{
	return new (GC) mu::llvmc::skeleton::instruction (region_a, branch_a, arguments_a, predicate_position_a);
}

mu::llvmc::skeleton::instruction * mu::llvmc::skeleton::factory::instruction (mu::core::region const & region_a, mu::llvmc::skeleton::branch * branch_a, std::initializer_list <mu::llvmc::skeleton::node *> arguments, std::initializer_list <mu::llvmc::skeleton::node *> predicates)
{
	return new (GC) mu::llvmc::skeleton::instruction (region_a, branch_a, arguments, predicates);
}

mu::llvmc::skeleton::struct_type * mu::llvmc::skeleton::factory::struct_type ()
{
	return new (GC) mu::llvmc::skeleton::struct_type;
}

mu::llvmc::skeleton::call_element * mu::llvmc::skeleton::factory::call_element (mu::core::region const & region_a, mu::llvmc::skeleton::branch * branch_a, mu::llvmc::skeleton::function_call * source_a, mu::llvmc::skeleton::type * type_a)
{
	return new (GC) mu::llvmc::skeleton::call_element (region_a, branch_a, source_a, type_a);
}

mu::llvmc::skeleton::integer_type * mu::llvmc::skeleton::factory::integer_type (size_t bits_a)
{
	return new (GC) mu::llvmc::skeleton::integer_type (bits_a);
}

mu::llvmc::skeleton::loop_element * mu::llvmc::skeleton::factory::loop_element (mu::core::region const & region_a, mu::llvmc::skeleton::branch * branch_a, mu::llvmc::skeleton::loop * source_a, mu::llvmc::skeleton::type * type_a)
{
	return new (GC) mu::llvmc::skeleton::loop_element (region_a, branch_a, source_a, type_a);
}

mu::llvmc::skeleton::pointer_type * mu::llvmc::skeleton::factory::pointer_type (mu::llvmc::skeleton::type * type_a)
{
	return new (GC) mu::llvmc::skeleton::pointer_type (type_a);
}

mu::llvmc::skeleton::function_type * mu::llvmc::skeleton::factory::function_type (mu::llvmc::skeleton::function * function_a)
{
	return new (GC) mu::llvmc::skeleton::function_type (function_a);
}

mu::llvmc::skeleton::constant_array * mu::llvmc::skeleton::factory::constant_array (mu::core::region const & region_a, mu::llvmc::skeleton::fixed_array_type * type_a, mu::vector <mu::llvmc::skeleton::constant *> const & initializer_a)
{
	return new (GC) mu::llvmc::skeleton::constant_array (region_a, type_a, initializer_a);
}

mu::llvmc::skeleton::loop_parameter * mu::llvmc::skeleton::factory::loop_parameter (mu::core::region const & region_a, mu::llvmc::skeleton::branch * branch_a, mu::llvmc::skeleton::type * type_a, mu::string const & name_a)
{
	return new (GC) mu::llvmc::skeleton::loop_parameter (region_a, branch_a, type_a, name_a);
}

mu::llvmc::skeleton::switch_element * mu::llvmc::skeleton::factory::switch_element (mu::core::region const & region_a, mu::llvmc::skeleton::branch * branch_a, mu::llvmc::skeleton::switch_i * source_a, mu::llvmc::skeleton::constant_integer * value_a)
{
	return new (GC) mu::llvmc::skeleton::switch_element (region_a, branch_a, source_a, value_a);
}

mu::llvmc::skeleton::global_variable * mu::llvmc::skeleton::factory::global_variable (mu::core::region const & region_a, mu::llvmc::skeleton::constant * initializer_a)
{
	return new (GC) mu::llvmc::skeleton::global_variable (region_a, initializer_a);
}

mu::llvmc::skeleton::constant_integer * mu::llvmc::skeleton::factory::constant_integer (mu::core::region const & region_a, mu::llvmc::skeleton::integer_type * type_a, uint64_t value_a)
{
	return new (GC) mu::llvmc::skeleton::constant_integer (region_a, type_a, value_a);
}

mu::llvmc::skeleton::constant_pointer_null * mu::llvmc::skeleton::factory::constant_pointer_null (mu::core::region const & region_a, mu::llvmc::skeleton::type * type_a)
{
	return new (GC) mu::llvmc::skeleton::constant_pointer_null (region_a, type_a);
}

mu::llvmc::skeleton::constant_aggregate_zero * mu::llvmc::skeleton::factory::constant_aggregate_zero (mu::core::region const & region_a, mu::llvmc::skeleton::type * type_a)
{
	return new (GC) mu::llvmc::skeleton::constant_aggregate_zero (region_a, type_a);
}

mu::llvmc::skeleton::asm_c * mu::llvmc::skeleton::factory::asm_c (mu::llvmc::skeleton::type * type_a, mu::string const & text_a, mu::string const & constraint_a)
{
	return new (GC) mu::llvmc::skeleton::asm_c (type_a, text_a, constraint_a);
}

mu::llvmc::skeleton::named * mu::llvmc::skeleton::factory::named (mu::core::region const & region_a, mu::llvmc::skeleton::value * value_a, mu::string const & name_a)
{
	return new (GC) mu::llvmc::skeleton::named (region_a, value_a, name_a);
}

mu::llvmc::skeleton::marker * mu::llvmc::skeleton::factory::marker (mu::llvmc::instruction_type type_a)
{
	return new (GC) mu::llvmc::skeleton::marker (type_a);
}

mu::llvmc::skeleton::result * mu::llvmc::skeleton::factory::result (mu::llvmc::skeleton::type * type_a, mu::llvmc::skeleton::value * value_a)
{
	return new (GC) mu::llvmc::skeleton::result (type_a, value_a);
}

mu::llvmc::skeleton::function * mu::llvmc::skeleton::factory::function (mu::core::region const & region_a)
{
	return new (GC) mu::llvmc::skeleton::function (region_a);
}

mu::llvmc::skeleton::identity * mu::llvmc::skeleton::factory::identity ()
{
	return new (GC) mu::llvmc::skeleton::identity;
}

mu::llvmc::skeleton::parameter * mu::llvmc::skeleton::factory::parameter (mu::core::region const & region_a, mu::llvmc::skeleton::branch * branch_a, mu::llvmc::skeleton::type * type_a, mu::string const & name_a)
{
	return new (GC) mu::llvmc::skeleton::parameter (region_a, branch_a, type_a, name_a);
}

mu::llvmc::skeleton::predicate * mu::llvmc::skeleton::factory::predicate (mu::llvmc::predicates type_a)
{
	return new (GC) mu::llvmc::skeleton::predicate (type_a);
}

mu::llvmc::skeleton::unit_type * mu::llvmc::skeleton::factory::unit_type ()
{
	return new (GC) mu::llvmc::skeleton::unit_type;
}

mu::llvmc::skeleton::identity_element * mu::llvmc::skeleton::factory::identity_element (mu::llvmc::skeleton::branch * branch_a, mu::llvmc::skeleton::identity_call * source_a, mu::llvmc::skeleton::type * type_a)
{
	return new (GC) mu::llvmc::skeleton::identity_element (branch_a, source_a, type_a);
}

mu::llvmc::skeleton::icmp * mu::llvmc::skeleton::factory::icmp (mu::core::region const & region_a, mu::llvmc::skeleton::branch * branch_a, mu::llvmc::skeleton::type * type_a, mu::llvmc::skeleton::predicate * predicate_a, mu::llvmc::skeleton::value * left_a, mu::llvmc::skeleton::value * right_a)
{
	return new (GC) mu::llvmc::skeleton::icmp (region_a, branch_a, type_a, predicate_a, left_a, right_a);
}

mu::llvmc::skeleton::store * mu::llvmc::skeleton::factory::store (mu::core::region const & region_a, mu::llvmc::skeleton::branch * branch_a, mu::llvmc::skeleton::type * type_a, mu::llvmc::skeleton::value * source_a, mu::llvmc::skeleton::value * destination_a)
{
	return new (GC) mu::llvmc::skeleton::store (region_a, branch_a, type_a, source_a, destination_a);
}

mu::llvmc::skeleton::undefined * mu::llvmc::skeleton::factory::undefined (mu::core::region const & region_a, mu::llvmc::skeleton::branch * branch_a, mu::llvmc::skeleton::type * type_a)
{
	return new (GC) mu::llvmc::skeleton::undefined (region_a, branch_a, type_a);
}

mu::llvmc::skeleton::template_c * mu::llvmc::skeleton::factory::template_c (mu::llvmc::template_context * base_a)
{
	return new (GC) mu::llvmc::skeleton::template_c (base_a);
}

mu::llvmc::skeleton::module * mu::llvmc::skeleton::factory::module ()
{
	return new (GC) mu::llvmc::skeleton::module;
}

mu::llvmc::skeleton::constant_int_c * mu::llvmc::skeleton::factory::constant_int_c ()
{
	return new (GC) mu::llvmc::skeleton::constant_int_c;
}

mu::llvmc::skeleton::instruction::instruction (mu::core::region const & region_a, mu::llvmc::skeleton::branch * branch_a, std::initializer_list <mu::llvmc::skeleton::node *> arguments_a, std::initializer_list <mu::llvmc::skeleton::node *> predicates_a) :
value (region_a, branch_a),
predicate_position (arguments_a.size ())
{
    arguments.insert (arguments.end (), arguments_a.begin (), arguments_a.end ());
    arguments.insert (arguments.end (), predicates_a.begin (), predicates_a.end ());
}

mu::llvmc::skeleton::value * mu::llvmc::skeleton::node::adapt (mu::llvmc::skeleton::type * target_type_a, mu::llvmc::function_processor & function_a, std::function <mu::core::error * (mu::core::region const &)> error_action_a)
{
    function_a.module_m.global_m.error = error_action_a (mu::empty_region);
    return nullptr;
}

mu::llvmc::skeleton::struct_type::struct_type (std::initializer_list <mu::llvmc::skeleton::type *> types_a) :
elements (types_a)
{
}

mu::string mu::llvmc::skeleton::type::name ()
{
	return U"type";
}

mu::string mu::llvmc::skeleton::function_type::name ()
{
	mu::string result;
	auto first (true);
	result.append (U"function [");
	for (auto i: function->parameters)
	{
		if (!first)
		{
			result.push_back (U' ');
		}
		first = false;
		result.append (i->type ()->name ());
	}
	result.push_back (U']');
	result.push_back (U' ');
	result.push_back (U'[');
	first = true;
    for (auto & i: function->results.branches)
    {
        result.push_back (U'[');
        for (auto j: i.results)
        {
            if (!first)
            {
                result.push_back (U' ');
            }
            first = false;
            result.append (j->type->name ());
        }
        result.push_back (']');
        first = true;
    }
	result.push_back (U']');
	return result;
}

mu::string mu::llvmc::skeleton::integer_type::name ()
{
	boost::format formatter ("int%1%");
	formatter % bits;
	std::string astring (formatter.str ().c_str ());
	mu::string result (astring.begin (), astring.end ());
	return result;
}

mu::string mu::llvmc::skeleton::fixed_array_type::name ()
{
	boost::format formatter ("%1%");
	formatter % size;
	std::string astring (formatter.str ().c_str ());
	mu::string result (U"farray ");
	result.append (element->name ());
	result.push_back (U' ');
	result.push_back (U'#');
	result.append (astring.begin (), astring.end ());
	return result;
}

mu::string mu::llvmc::skeleton::struct_type::name ()
{
	mu::string result (U"struct [");
	for (auto i: elements)
	{
		result.append (i->name ());
	}
	result.push_back (']');
	return result;
}

mu::string mu::llvmc::skeleton::unit_type::name ()
{
	mu::string result (U"unit");
	return result;
}

mu::string mu::llvmc::skeleton::pointer_type::name ()
{
	mu::string result (U"ptr ");
	result.append (pointed_type->name ());
	return result;
}

mu::llvmc::skeleton::value * mu::llvmc::skeleton::number::adapt_constant_integer (mu::llvmc::skeleton::type * target_type_a, mu::llvmc::function_processor & function_a, std::function <mu::core::error * (mu::core::region const &)> error_action_a)
{
    mu::llvmc::skeleton::value * result;
	auto integer_type (dynamic_cast <mu::llvmc::skeleton::integer_type *> (target_type_a));
    if (integer_type != nullptr)
    {
        auto bits (bits_required ());
        if (bits <= integer_type->bits)
        {
            result = b.constant_integer (mu::core::region (), integer_type, value);
        }
        else
        {
            function_a.module_m.global_m.error = error_action_a (mu::core::region ());
            result = nullptr;
        }
    }
    else
    {
        function_a.module_m.global_m.error = error_action_a (mu::core::region ());
        result = nullptr;
    }
    return result;
}

mu::llvmc::skeleton::value * mu::llvmc::skeleton::number::adapt (mu::llvmc::skeleton::type * target_type_a, mu::llvmc::function_processor & function_a, std::function <mu::core::error * (mu::core::region const &)> error_action_a)
{
	return adapt_constant_integer (target_type_a, function_a, error_action_a);
}

mu::llvmc::skeleton::value * mu::llvmc::skeleton::number::adapt_result (mu::llvmc::skeleton::type * target_type_a, mu::llvmc::function_processor & function_a, std::function <mu::core::error * (mu::core::region const &)> error_action_a)
{
	return adapt_constant_integer (target_type_a, function_a, error_action_a);
}

unsigned mu::llvmc::skeleton::number::bits_required ()
{
    uint64_t value_l (value);
    unsigned result (value_l ? 0 : 1);
    while (value_l)
    {
        ++result;
        value_l >>= 1;
    }
    return result;
}

void mu::llvmc::skeleton::number::visit (mu::llvmc::skeleton::visitor * visitor_a)
{
	visitor_a->number (this);
}

mu::llvmc::skeleton::function_result::function_result (std::initializer_list <mu::llvmc::skeleton::result *> const & results_a, std::initializer_list <mu::llvmc::skeleton::sequence *> const & sequenced_a) :
results (results_a),
sequenced (sequenced_a)
{
}

mu::llvmc::skeleton::function_branches::function_branches (std::initializer_list <function_result> const & branches_a) :
branches (branches_a)
{
}

mu::llvmc::skeleton::function_result & mu::llvmc::skeleton::function_branches::add_branch ()
{
    branches.push_back (mu::llvmc::skeleton::function_result ());
    return branches.back ();
}

size_t mu::llvmc::skeleton::function_branches::size () const
{
    return branches.size ();
}

mu::llvmc::skeleton::function_result & mu::llvmc::skeleton::function_branches::operator [] (size_t index)
{
    assert (branches.size () > index);
    return branches [index];
}

mu::llvmc::skeleton::sequence::sequence (mu::llvmc::skeleton::value * value_a) :
value (value_a)
{
}

void mu::llvmc::skeleton::sequence::visit (mu::llvmc::skeleton::visitor * visitor_a)
{
    visitor_a->sequence (this);
}