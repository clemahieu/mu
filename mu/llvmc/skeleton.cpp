#include <mu/llvmc/skeleton.hpp>

#include <mu/llvmc/analyzer.hpp>
#include <mu/core/error_string.hpp>

#include <gc_cpp.h>

mu::llvmc::skeleton::element::element (mu::llvmc::skeleton::branch * branch_a, mu::llvmc::skeleton::call * call_a, size_t branch_index_a, size_t result_index_a) :
value (branch_a),
call (call_a),
branch_index (branch_index_a),
result_index (result_index_a)
{
}

mu::llvmc::skeleton::node::~node ()
{
}

mu::llvmc::skeleton::function::function () :
value (nullptr),
type_m (*this),
entry (nullptr)
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

mu::llvmc::skeleton::instruction::instruction (mu::llvmc::skeleton::branch * branch_a, mu::llvmc::instruction_type type_a) :
value (branch_a),
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

mu::llvmc::skeleton::type * mu::llvmc::skeleton::function::type ()
{
    return & type_m;
}

void mu::llvmc::skeleton::value::process_arguments (mu::llvmc::analyzer_function & analyzer_a, mu::llvmc::ast::node * node_a, mu::vector <mu::llvmc::skeleton::node *> & arguments_a)
{
    assert (arguments_a [0] == this);
    auto type_l (type ());
    auto pointer_type (dynamic_cast <mu::llvmc::skeleton::pointer_type *> (type_l));
    if (pointer_type != nullptr)
    {
        auto function_type (dynamic_cast <mu::llvmc::skeleton::function_type *> (pointer_type->pointed_type));
        if (function_type != nullptr)
        {
            if (arguments_a.size () == function_type->function.parameters.size ())
            {
                auto k (arguments_a.begin ());
                for (auto i (function_type->begin_parameters ()), j (function_type->end_parameters ()); i != j && analyzer_a.result_m.error
                      == nullptr; ++i, ++k)
                {
                    auto argument_value (dynamic_cast <mu::llvmc::skeleton::value *> (*k));
                    if (argument_value != nullptr)
                    {
                        if ((*argument_value->type ()) != **i)
                        {
                            analyzer_a.result_m.error = new (GC) mu::core::error_string (U"Argument type does not match parameter type");
                        }
                    }
                    else
                    {
                        analyzer_a.result_m.error = new (GC) mu::core::error_string (U"Argument to function is not a value");
                    }
                }
                if (analyzer_a.result_m.error == nullptr)
                {
                    mu::llvmc::skeleton::branch * most_specific_branch (nullptr);
                    if (!arguments_a.empty ())
                    {
                        auto value (dynamic_cast <mu::llvmc::skeleton::value *> (arguments_a [0]));
                        assert (value != nullptr);
                        most_specific_branch = value->branch;
                        for (auto i (arguments_a.begin () + 1), j (arguments_a.end ()); i != j && analyzer_a.result_m.error == nullptr; ++i)
                        {
                            auto value (dynamic_cast <mu::llvmc::skeleton::value *> (*i));
                            assert (value != nullptr);
                            auto testing (value->branch);
                            while (testing != nullptr && testing != most_specific_branch)
                            {
                                testing = testing->parent;
                            }
                            if (testing == nullptr)
                            {
                                // Previous most specific branch was not above or equal to the current one
                                // Current one must be most specific branch or these arguments are disjoint
                                testing = most_specific_branch;
                                most_specific_branch = value->branch;
                                while (testing != nullptr && testing != most_specific_branch)
                                {
                                    testing = testing->parent;
                                }
                                if (testing == nullptr)
                                {
                                    analyzer_a.result_m.error = new (GC) mu::core::error_string (U"Arguments are disjoint");                                        
                                }
                            }
                        }
                        if (analyzer_a.result_m.error == nullptr)
                        {
                            auto call (new (GC) mu::llvmc::skeleton::call (function_type, most_specific_branch, arguments_a));
                            if (function_type->function.results.size () == 1)
                            {
                                if (function_type->function.results [0].size () == 1)
                                {
                                    analyzer_a.already_generated [node_a] = new (GC) mu::llvmc::skeleton::element (most_specific_branch, call, 0, 0);
                                }
                                else
                                {
                                    auto & target (analyzer_a.already_generated_multi [node_a]);
                                    for (size_t i (0), j (function_type->function.results [0].size ()); i != j && analyzer_a.result_m.error == nullptr; ++i)
                                    {
                                        target.push_back (new (GC) mu::llvmc::skeleton::element (most_specific_branch, call, 0, i));
                                    }
                                }
                            }
                            else
                            {
                                for (size_t i (0), j (function_type->function.results.size ()); i != j && analyzer_a.result_m.error == nullptr; ++i)
                                {
                                    auto branch (new (GC) mu::llvmc::skeleton::branch (most_specific_branch));
                                    if (function_type->function.results [0].size () == 1)
                                    {
                                        analyzer_a.already_generated [node_a] = new (GC) mu::llvmc::skeleton::element (branch, call, i, 0);
                                    }
                                    else
                                    {
                                        auto & target (analyzer_a.already_generated_multi [node_a]);
                                        for (size_t k (0), l (function_type->function.results [i].size ()); k != l && analyzer_a.result_m.error == nullptr; ++k)
                                        {
                                            target.push_back (new (GC) mu::llvmc::skeleton::element (branch, call, i, k));
                                        }
                                    }
                                }                                
                            }
                        }
                    }
                }
            }
            else
            {
                analyzer_a.result_m.error = new (GC) mu::core::error_string (U"Number of arguments does not match number of parameters");
            }
        }
        else
        {
            analyzer_a.result_m.error = new (GC) mu::core::error_string (U"Pointer does not point to a function");
        }
    }
    else
    {
        analyzer_a.result_m.error = new (GC) mu::core::error_string (U"Only function pointers can be the target of a call");
    }
}

mu::llvmc::skeleton::pointer_type::pointer_type (mu::llvmc::skeleton::type * type_a):
pointed_type (type_a)
{
}

mu::llvmc::skeleton::type * mu::llvmc::skeleton::element::type ()
{
    assert (call->type->function.results.size () > branch_index);
    assert (call->type->function.results [branch_index].size () > result_index);
    auto result (call->type->function.results [branch_index][result_index]->type);
    return result;
}

mu::llvmc::skeleton::type * mu::llvmc::skeleton::parameter::type ()
{
    auto result (type_m);
    return result;
}

mu::llvmc::skeleton::parameter_iterator::parameter_iterator (mu::llvmc::skeleton::function & function_a, size_t index_a) :
index (index_a),
function (function_a)
{
}

mu::llvmc::skeleton::type * mu::llvmc::skeleton::parameter_iterator::operator * () const
{
    assert (index < function.parameters.size ());
    auto result (function.parameters [index]);
    return result->type_m;    
}

void mu::llvmc::skeleton::parameter_iterator::operator ++ ()
{
    assert (index < function.parameters.size ());
    ++index;
}

bool mu::llvmc::skeleton::parameter_iterator::operator == (mu::llvmc::skeleton::parameter_iterator const & other_a) const
{
    auto result (index == other_a.index);
    return result;
}

bool mu::llvmc::skeleton::parameter_iterator::operator != (mu::llvmc::skeleton::parameter_iterator const & other_a) const
{
    auto result (!((*this) == other_a));
    return result;
}

mu::llvmc::skeleton::parameter_iterator mu::llvmc::skeleton::function_type::begin_parameters ()
{
    mu::llvmc::skeleton::parameter_iterator result (function, 0);
    return result;
}

mu::llvmc::skeleton::parameter_iterator mu::llvmc::skeleton::function_type::end_parameters ()
{
    mu::llvmc::skeleton::parameter_iterator result (function, function.parameters.size ());
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

mu::llvmc::skeleton::call::call (mu::llvmc::skeleton::function_type * type_a, mu::llvmc::skeleton::branch * branch_a, mu::vector <mu::llvmc::skeleton::node *> & arguments_a):
type (type_a),
branch (branch_a),
arguments (arguments_a)
{
}