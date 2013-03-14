#include <mu/llvmc/analyzer.hpp>

#include <mu/core/error_string.hpp>
#include <mu/llvmc/ast.hpp>
#include <mu/llvmc/skeleton.hpp>

#include <gc_cpp.h>

mu::llvmc::module_result mu::llvmc::analyzer::analyze (mu::llvmc::ast::node * module_a)
{
    mu::llvmc::analyzer_module analyzer_l;
    auto result (analyzer_l.analyze (module_a));
    return result;
}

mu::llvmc::analyzer_module::analyzer_module () :
module (new (GC) mu::llvmc::skeleton::module),
result_m ({nullptr, nullptr})
{
}

mu::llvmc::analyzer_function::analyzer_function (mu::llvmc::analyzer_module & module_a) :
result_m ({nullptr, nullptr}),
module (module_a)
{    
}

void mu::llvmc::analyzer_function::process_parameters (mu::llvmc::ast::function * function_a, mu::llvmc::skeleton::function * function_s)
{
    for (auto k (function_a->parameters.begin ()), l (function_a->parameters.end ()); k != l && result_m.error == nullptr; ++k)
    {
        auto type_l (process_type ((*k)->type));
        if (type_l != nullptr)
        {
            auto parameter_s (new (GC) mu::llvmc::skeleton::parameter (function_s->entry, type_l));
            already_generated [*k] = parameter_s;
            function_s->parameters.push_back (parameter_s);
        }
        else
        {
            result_m.error = new (GC) mu::core::error_string (U"Expecting a type");
        }
    }
}

bool mu::llvmc::analyzer_function::process_node (mu::llvmc::ast::node * node_a)
{
    auto result (false);
    auto existing (already_generated.find (node_a));
    if (existing == already_generated.end ())
    {
        auto existing_multi (already_generated_multi.find (node_a));
        if (existing_multi == already_generated_multi.end ())
        {
            auto existing_function (module.functions.find (node_a));
            if (existing_function == module.functions.end ())
            {
                auto definite_expression (dynamic_cast <mu::llvmc::ast::definite_expression *> (node_a));
                if (definite_expression != nullptr)
                {
                    result = process_definite_expression (definite_expression);
                }
                else
                {
                    auto value_node (dynamic_cast <mu::llvmc::ast::value *> (node_a));
                    if (value_node != nullptr)
                    {
                        already_generated [node_a] = value_node->node_m;
                    }
                    else
                    {
                        auto element_node (dynamic_cast <mu::llvmc::ast::element *> (node_a));
                        if (element_node != nullptr)
                        {
                            process_element (element_node);
                        }
                        else
                        {
                            result_m.error = new (GC) mu::core::error_string (U"Unknown expression subclass");
                        }
                    }
                }
            }
            else
            {
                already_generated [node_a] = existing_function->second;
            }
        }
        else
        {
            result = true;
        }
    }
    return result;
}

void mu::llvmc::analyzer_function::process_element (mu::llvmc::ast::element * element_a)
{
    auto multi (process_node (element_a->node));
    if (result_m.error == nullptr)
    {
        if (multi)
        {
            auto existing (already_generated_multi.find (element_a->node));
            if (existing->second.size () > element_a->index)
            {
                already_generated [element_a] = existing->second [element_a->index];
            }
            else
            {
                result_m.error = new (GC) mu::core::error_string (U"No value at index");
            }
        }
        else
        {
            if (element_a->index == 0)
            {
                already_generated [element_a] = already_generated [element_a->node];
            }
            else
            {
                result_m.error = new (GC) mu::core::error_string (U"Value has only one element");
            }
        }
    }
}

void mu::llvmc::analyzer_function::process_single_node (mu::llvmc::ast::node * node_a)
{
    auto multi (process_node (node_a));
    if (multi)
    {
        result_m.error = new (GC) mu::core::error_string (U"Expecting 1 value");
    }
}

mu::llvmc::skeleton::value * mu::llvmc::analyzer_function::process_value (mu::llvmc::ast::node * node_a)
{
    mu::llvmc::skeleton::value * result (nullptr);
    process_single_node (node_a);
    if (result_m.error == nullptr)
    {
        result = dynamic_cast <mu::llvmc::skeleton::value *> (already_generated [node_a]);
        if (result == nullptr)
        {
            result_m.error = new (GC) mu::core::error_string (U"Node is not value");
        }
    }
    return result;
}

mu::llvmc::skeleton::type * mu::llvmc::analyzer_function::process_type (mu::llvmc::ast::node * node_a)
{
    mu::llvmc::skeleton::type * result (nullptr);
    process_single_node (node_a);
    if (result_m.error == nullptr)
    {
        auto node_l (already_generated [node_a]);
        result = dynamic_cast <mu::llvmc::skeleton::type *> (node_l);
    }
    return result;
}

void mu::llvmc::analyzer_function::process_results(mu::llvmc::ast::function * function_a, mu::llvmc::skeleton::function * function_s)
{
    mu::set <mu::llvmc::skeleton::branch *> result_branches;
    for (auto k (function_a->results.begin ()), l (function_a->results.end ()); k != l && result_m.error == nullptr; ++k)
    {
        auto most_specific_branch (module.module->global);
        auto & ast_result (*k);
        function_s->results.push_back (decltype (function_s->results)::value_type ());
        auto & new_result (function_s->results [function_s->results.size () - 1]);
        for (auto m (ast_result.begin ()), n (ast_result.end ()); m != n && result_m.error == nullptr; ++m)
        {
            auto single_result (*m);
            auto type (process_type (single_result->written_type));
            if (type != nullptr)
            {
                auto value (process_value (single_result->value));
                if (value != nullptr)
                {
                    new_result.push_back (new (GC) mu::llvmc::skeleton::result (type, value));
                    most_specific_branch = most_specific_branch->most_specific (value->branch);
                }
            }
            else
            {
                result_m.error = new (GC) mu::core::error_string (U"Expecting a type");
            }
        }
        auto existing (result_branches.find (most_specific_branch));
        if (existing == result_branches.end ())
        {
            result_branches.insert (most_specific_branch);
        }
        else
        {
            result_m.error = new (GC) mu::core::error_string (U"Result branch is not distinct");
        }
    }
}

mu::llvmc::function_result mu::llvmc::analyzer_function::analyze (mu::llvmc::ast::node * function_a)
{
    auto function_l (dynamic_cast <mu::llvmc::ast::function *> (function_a));
    if (function_l != nullptr)
    {
        auto function_s (new (GC) mu::llvmc::skeleton::function (module.module->global));
        process_parameters (function_l, function_s);
        process_results (function_l, function_s);
        result_m.function = function_s;
    }
    else
    {
        result_m.error = new (GC) mu::core::error_string (U"Expecting a function");
    }
    return result_m;
}

mu::llvmc::module_result mu::llvmc::analyzer_module::analyze (mu::llvmc::ast::node * module_a)
{
    auto module_s (module);
    auto module_l (dynamic_cast <mu::llvmc::ast::module *> (module_a));
    if (module_l != nullptr)
    {
        for (auto i (module_l->functions.begin ()), j (module_l->functions.end ()); i != j && result_m.error == nullptr; ++i)
        {
            analyzer_function analyzer (*this);
            analyzer.analyze (*i);
            module_s->functions.push_back (analyzer.result_m.function);
            result_m.error = analyzer.result_m.error;
        }
    }
    else
    {
        result_m.error = new (GC) mu::core::error_string (U"Expecting a module");
    }
    if (result_m.error == nullptr)
    {
        result_m.module = module_s;
    }
    return result_m;
}

bool mu::llvmc::analyzer_function::process_definite_expression (mu::llvmc::ast::definite_expression * expression_a)
{
    auto result (false);
    auto existing (current_expression_generation.find (expression_a));
    if (existing == current_expression_generation.end ())
    {
        current_expression_generation.insert (expression_a);
        mu::vector <mu::llvmc::skeleton::node *> arguments;
        mu::vector <mu::llvmc::skeleton::node *> predicates;
        mu::llvmc::skeleton::branch * most_specific_branch (module.module->global);
        for (auto i (expression_a->arguments.begin ()), j (expression_a->arguments.end ()); i != j && result_m.error == nullptr; ++i)
        {
            result = (process_node (*i));
            if (result_m.error == nullptr)
            {
                if (result)
                {
                    auto & nodes (already_generated_multi [*i]);
                    for (auto k (nodes.begin ()), l (nodes.end ()); k != l && result_m.error == nullptr; ++k)
                    {
                        auto node (*k);
                        auto bottom (false);
                        auto value (dynamic_cast <mu::llvmc::skeleton::value *> (node));
                        if (value != nullptr)
                        {
                            calculate_most_specific (most_specific_branch, value->branch);
                            bottom = value->type ()->is_bottom_type ();
                        }
                        if (!bottom)
                        {
                            arguments.push_back (node);
                        }
                        else
                        {
                            predicates.push_back (node);
                        }
                    }
                }
                else
                {
                    auto node (already_generated [*i]);
                    auto bottom (false);
                    auto value (dynamic_cast <mu::llvmc::skeleton::value *> (node));
                    if (value != nullptr)
                    {
                        calculate_most_specific (most_specific_branch, value->branch);
                        bottom = value->type ()->is_bottom_type ();
                    }
                    if (!bottom)
                    {
                        arguments.push_back (node);
                    }
                    else
                    {
                        predicates.push_back (node);
                    }
                }
            }
        }
        if (result_m.error == nullptr)
        {
            if (!arguments.empty ())
            {
                auto target (dynamic_cast <mu::llvmc::skeleton::value *> (arguments [0]));
                if (target != nullptr)
                {
                    result = process_value_call (arguments, predicates, most_specific_branch, expression_a);
                }
                else
                {
                    auto marker (dynamic_cast <mu::llvmc::skeleton::marker *> (arguments [0]));
                    if (marker != nullptr)
                    {
                        result = process_marker (arguments, predicates, most_specific_branch, expression_a);
                    }
                    else
                    {
                        result_m.error = new (GC) mu::core::error_string (U"Expecting first argument to be call target");
                    }
                }
            }
            else
            {
                result_m.error = new (GC) mu::core::error_string (U"Expecting a call target");
            }
        }
        current_expression_generation.erase (expression_a);
    }
    else
    {
        result_m.error = new (GC) mu::core::error_string (U"Cycle in expressions");
    }
    return result;
}

bool mu::llvmc::analyzer_function::process_value_call (mu::vector <mu::llvmc::skeleton::node *> & arguments_a, mu::vector <mu::llvmc::skeleton::node *> & predicates_a, mu::llvmc::skeleton::branch * branch_a, mu::llvmc::ast::node * expression_a)
{
    auto result (false);
    assert (! arguments_a.empty ());
    assert (dynamic_cast <mu::llvmc::skeleton::value *> (arguments_a [0]) != nullptr);
    auto target (static_cast <mu::llvmc::skeleton::value *> (arguments_a [0]));
    auto type_l (target->type ());
    auto pointer_type (dynamic_cast <mu::llvmc::skeleton::pointer_type *> (type_l));
    if (pointer_type != nullptr)
    {
        auto function_type (dynamic_cast <mu::llvmc::skeleton::function_type *> (pointer_type->pointed_type));
        if (function_type != nullptr)
        {
            auto k (arguments_a.begin ());
            auto l (arguments_a.end ());
            for (size_t i (0), j (function_type->function.parameters.size ()); i != j && k != l && result_m.error
                 == nullptr; ++i, ++k)
            {
                auto argument_value (dynamic_cast <mu::llvmc::skeleton::value *> (*k));
                if (argument_value != nullptr)
                {         
                    if ((*argument_value->type ()) != *function_type->function.parameters [i]->type ())
                    {
                        result_m.error = new (GC) mu::core::error_string (U"Argument type does not match parameter type");
                    }
                }
                else
                {
                    result_m.error = new (GC) mu::core::error_string (U"Argument to function is not a value");
                }
            }
            if (result_m.error == nullptr)
            {
                if (!arguments_a.empty ())
                {
                    auto call (new (GC) mu::llvmc::skeleton::function_call (function_type->function, branch_a, arguments_a, predicates_a));
                    if (function_type->function.results.size () == 1)
                    {
                        if (function_type->function.results [0].size () == 1)
                        {
                            already_generated [expression_a] = new (GC) mu::llvmc::skeleton::call_element (branch_a, call, 0, 0);
                        }
                        else
                        {
                            result = true;
                            auto & target (already_generated_multi [expression_a]);
                            for (size_t i (0), j (function_type->function.results [0].size ()); i != j && result_m.error == nullptr; ++i)
                            {
                                target.push_back (new (GC) mu::llvmc::skeleton::call_element (branch_a, call, 0, i));
                            }
                        }
                    }
                    else
                    {
                        result = true;
                        for (size_t i (0), j (function_type->function.results.size ()); i != j && result_m.error == nullptr; ++i)
                        {
                            auto branch (new (GC) mu::llvmc::skeleton::branch (branch_a));
                            if (function_type->function.results [0].size () == 1)
                            {
                                already_generated [expression_a] = new (GC) mu::llvmc::skeleton::call_element (branch, call, i, 0);
                            }
                            else
                            {
                                auto & target (already_generated_multi [expression_a]);
                                for (size_t k (0), l (function_type->function.results [i].size ()); k != l && result_m.error == nullptr; ++k)
                                {
                                    target.push_back (new (GC) mu::llvmc::skeleton::call_element (branch, call, i, k));
                                }
                            }
                        }
                    }
                }
            }
        }
        else
        {
            result_m.error = new (GC) mu::core::error_string (U"Pointer does not point to a function");
        }
    }
    else
    {
        result_m.error = new (GC) mu::core::error_string (U"Only function pointers can be the target of a call");
    }
    return result;
}

void mu::llvmc::analyzer_function::calculate_most_specific (mu::llvmc::skeleton::branch * & first, mu::llvmc::skeleton::branch * test)
{
    auto first_l (first->most_specific (test));
    if (first_l == nullptr)
    {
        result_m.error = new (GC) mu::core::error_string (U"Arguments are disjoint");
    }
    else
    {
        first = first_l;
    }
}

bool mu::llvmc::analyzer_function::process_marker (mu::vector <mu::llvmc::skeleton::node *> & arguments_a, mu::vector <mu::llvmc::skeleton::node *> & predicates_a, mu::llvmc::skeleton::branch * branch_a, mu::llvmc::ast::node * expression_a)
{
    assert (!arguments_a.empty ());
    assert (dynamic_cast <mu::llvmc::skeleton::marker *> (arguments_a [0]) != nullptr);
    auto marker (static_cast <mu::llvmc::skeleton::marker *> (arguments_a [0]));
    auto result (false);
    switch (marker->type)
    {
        case mu::llvmc::instruction_type::if_i:
        {
            if (arguments_a.size () == 2)
            {
                auto predicate (dynamic_cast <mu::llvmc::skeleton::value *> (arguments_a [1]));
                if (predicate != nullptr)
                {
                    auto integer_type (dynamic_cast <mu::llvmc::skeleton::integer_type *> (predicate->type ()));
                    if (integer_type != nullptr)
                    {
                        if (integer_type->bits == 1)
                        {
                            result = true;
                            auto switch_i (new (GC) mu::llvmc::skeleton::instruction (branch_a, arguments_a, predicates_a, mu::llvmc::instruction_type::switch_i));
                            auto true_branch (new (GC) mu::llvmc::skeleton::branch (branch_a));
                            auto false_branch (new (GC) mu::llvmc::skeleton::branch (branch_a));
                            auto true_element (new (GC) mu::llvmc::skeleton::switch_element (true_branch, switch_i, new (GC) mu::llvmc::skeleton::constant_integer (1, 1)));
                            auto false_element (new (GC) mu::llvmc::skeleton::switch_element (false_branch, switch_i, new (GC) mu::llvmc::skeleton::constant_integer (1, 0)));
                            auto & values (already_generated_multi [expression_a]);
                            values.push_back (true_element);
                            values.push_back (false_element);
                        }
                        else
                        {
                            result_m.error = new (GC) mu::core::error_string (U"If instruction expects 1 bit integer");
                        }
                    }
                    else
                    {
                        result_m.error = new (GC) mu::core::error_string (U"If instruction expects an integer type value");
                    }
                }
                else
                {
                    result_m.error = new (GC) mu::core::error_string (U"If instruction expects a value argument");
                }
            }
            else
            {
                result_m.error = new (GC) mu::core::error_string (U"If instruction expects one argument");
            }
        }
            break;
        case mu::llvmc::instruction_type::add:
        {
            if (arguments_a.size () == 3)
            {
                auto left (dynamic_cast <mu::llvmc::skeleton::value *> (arguments_a [1]));
                if (left != nullptr)
                {
                    auto right (dynamic_cast <mu::llvmc::skeleton::value *> (arguments_a [2]));
                    if (right != nullptr)
                    {
                        auto left_type (dynamic_cast <mu::llvmc::skeleton::integer_type *> (left->type ()));
                        if (left_type != nullptr)
                        {
                            auto right_type (dynamic_cast <mu::llvmc::skeleton::integer_type *> (right->type ()));
                            if (right_type != nullptr)
                            {
                                if (left_type->bits == right_type->bits)
                                {
                                    if (result_m.error == nullptr)
                                    {
                                        already_generated [expression_a] = new (GC) mu::llvmc::skeleton::instruction (branch_a, arguments_a, predicates_a, mu::llvmc::instruction_type::add);
                                    }
                                }
                                else
                                {
                                    result_m.error = new (GC) mu::core::error_string (U"Add left and right arguments must be same width");
                                }
                            }
                            else
                            {
                                result_m.error = new (GC) mu::core::error_string (U"Add right argument must be an integer type");
                            }
                        }
                        else
                        {
                            result_m.error = new (GC) mu::core::error_string (U"Add left argument must be an integer type");
                        }
                    }
                    else
                    {
                        result_m.error = new (GC) mu::core::error_string (U"Add right argument must be a value");
                    }
                }
                else
                {
                    result_m.error = new (GC) mu::core::error_string (U"Add left argument must be a value");
                }
            }
            else
            {
                result_m.error = new (GC) mu::core::error_string (U"Add instruction expects two arguments");
            }
        }
            break;
        default:
            result_m.error = new (GC) mu::core::error_string (U"Unknown instruction marker");
            break;
    }
    return result;
}