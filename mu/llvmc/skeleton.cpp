#include <mu/llvmc/skeleton.hpp>

#include <mu/llvmc/analyzer.hpp>
#include <mu/core/error_string.hpp>

#include <gc_cpp.h>

mu::llvmc::skeleton::element::element (mu::llvmc::skeleton::branch * branch_a, mu::llvmc::skeleton::function * function_a, size_t result_index_a, size_t item_index_a) :
value (branch_a),
function (function_a),
result_index (result_index_a),
item_index (item_index_a)
{
}

mu::llvmc::skeleton::node::~node ()
{
}

mu::llvmc::skeleton::function::function () :
entry (nullptr)
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

mu::llvmc::skeleton::instruction::instruction (mu::llvmc::instruction_type type_a) :
type (type_a)
{
}

void mu::llvmc::skeleton::instruction::process_arguments (mu::llvmc::analyzer_function & analyzer_a, mu::llvmc::ast::node * node_a, mu::vector <mu::llvmc::skeleton::node *> & arguments_a)
{
    assert (arguments_a [0] == this);
    switch (type)
    {
        case mu::llvmc::instruction_type::add:
        {
            if (arguments_a.size () == 3)
            {
                
            }
            else
            {
                analyzer_a.result_m.error = new (GC) mu::core::error_string (U"Expecting two arguments");
            }
        }
            break;
        default:
            analyzer_a.result_m.error = new (GC) mu::core::error_string (U"Unknown instruction type");
            break;
    }
}

void mu::llvmc::skeleton::function::process_arguments (mu::llvmc::analyzer_function & analyzer_a, mu::llvmc::ast::node * node_a, mu::vector <mu::llvmc::skeleton::node *> & arguments_a)
{
    assert (arguments_a [0] == this);
}

mu::llvmc::skeleton::type * mu::llvmc::skeleton::element::type ()
{
    assert (function->results.size () > result_index);
    assert (function->results [result_index].size () > item_index);
    auto result (function->results [result_index][item_index]->type);
    return result;
}

mu::llvmc::skeleton::type * mu::llvmc::skeleton::parameter::type ()
{
    auto result (type_m);
    return result;
}