#include <mu/llvmc/analyzer.hpp>

#include <mu/core/error_string.hpp>
#include <mu/llvmc/ast.hpp>
#include <mu/llvmc/skeleton.hpp>

#include <gc_cpp.h>

mu::llvmc::module_result mu::llvmc::analyzer::analyze (mu::llvmc::ast::node * module_a)
{
    mu::llvmc::analyzer_routine analyzer_l;
    auto result (analyzer_l.analyze (module_a));
    return result;
}

mu::llvmc::analyzer_routine::analyzer_routine () :
result ({nullptr, nullptr})
{
}

mu::llvmc::module_result mu::llvmc::analyzer_routine::analyze (mu::llvmc::ast::node * module_a)
{
    auto module_s (new (GC) mu::llvmc::skeleton::module);
    auto module_l (dynamic_cast <mu::llvmc::ast::module *> (module_a));
    if (module_l != nullptr)
    {
        for (auto i (module_l->functions.begin ()), j (module_l->functions.end ()); i != j && result.error == nullptr; ++i)
        {
            auto function_l (dynamic_cast <mu::llvmc::ast::function *> (*i));
            if (function_l != nullptr)
            {
                auto function_s (new (GC) mu::llvmc::skeleton::function);
                module_s->functions.push_back (function_s);
                for (auto k (function_l->parameters.begin ()), l (function_l->parameters.end ()); k != l && result.error == nullptr; ++k)
                {
                    auto type_l (dynamic_cast <mu::llvmc::skeleton::type *> ((*k)->type));
                    if (type_l != nullptr)
                    {
                        function_s->parameters.push_back (mu::llvmc::skeleton::parameter (type_l));
                    }
                    else
                    {
                        result.error = new (GC) mu::core::error_string (U"Expecting a type");
                    }
                }
                for (auto k (function_l->results.begin ()), l (function_l->results.end ()); k != l && result.error == nullptr; ++k)
                {
                    auto & ast_result (*k);
                    function_s->results.push_back (decltype (function_s->results)::value_type ());
                    auto & new_result (function_s->results [function_s->results.size () - 1]);
                    for (auto m (ast_result.begin ()), n (ast_result.end ()); m != n && result.error == nullptr; ++m)
                    {
                        auto single_result (*m);
                        auto type_l (dynamic_cast <mu::llvmc::skeleton::type *> (single_result->written_type));
                        if (type_l != nullptr)
                        {
                            auto result_node (process_node (single_result->value));
                            auto expression (dynamic_cast <mu::llvmc::skeleton::expression *> (result_node));
                            if (expression != nullptr)
                            {
                                new_result.push_back (mu::llvmc::skeleton::result ({type_l, expression}));
                            }
                            else
                            {
                                result.error = new (GC) mu::core::error_string (U"Expecting expression");
                            }
                        }
                        else
                        {
                            result.error = new (GC) mu::core::error_string (U"Expecting a type");
                        }
                    }
                }
            }
            else
            {
                result.error = new (GC) mu::core::error_string (U"Expecting a function");
            }
        }
    }
    else
    {
        result.error = new (GC) mu::core::error_string (U"Expecting a module");
    }
    if (result.error == nullptr)
    {
        result.module = module_s;
    }
    return result;
}

mu::llvmc::skeleton::node * mu::llvmc::analyzer_routine::process_node (mu::llvmc::ast::node * node_a)
{
    mu::llvmc::skeleton::node * node_l (nullptr);
    auto expression (dynamic_cast <mu::llvmc::ast::expression *> (node_a));
    if (expression != nullptr)
    {
        auto existing (already_generated.find (expression));
        if (existing == already_generated.end ())
        {
            auto definite_expression (dynamic_cast <mu::llvmc::ast::definite_expression *> (node_a));
            if (definite_expression != nullptr)
            {
                node_l = process_definite_expression (definite_expression);
            }
            else
            {
                auto value_node (dynamic_cast <mu::llvmc::ast::value *> (node_a));
                if (value_node != nullptr)
                {
                    node_l = value_node->node_m;
                }
                else
                {
                    result.error = new (GC) mu::core::error_string (U"Unknown expression subclass");
                }
            }
            already_generated [node_a] = node_l;
        }
        else
        {
            node_l = existing->second;
        }
    }
    else
    {
        result.error = new (GC) mu::core::error_string (U"Expecting expression");
    }
    return node_l;
}

mu::llvmc::skeleton::definite_expression * mu::llvmc::analyzer_routine::process_definite_expression (mu::llvmc::ast::definite_expression * expression_a)
{
    auto result_l (new (GC) mu::llvmc::skeleton::definite_expression);
    auto existing (current_expression_generation.find (expression_a));
    if (existing == current_expression_generation.end ())
    {
        current_expression_generation.insert (expression_a);
        for (auto i (expression_a->arguments.begin ()), j (expression_a->arguments.end ()); i != j && result.error == nullptr; ++i)
        {
            auto node (process_node (*i));
            auto expression (dynamic_cast <mu::llvmc::skeleton::expression *> (node));
            if (expression != nullptr)
            {
                result_l->arguments.push_back (expression);
            }
            else
            {
                result.error = new (GC) mu::core::error_string (U"Expecting expression");
            }
        }
        current_expression_generation.erase (expression_a);
    }
    else
    {
        result.error = new (GC) mu::core::error_string (U"Cycle in expressions");
    }
    return result_l;
}