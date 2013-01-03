#include <mu/llvmc/parser.hpp>

#include <mu/core/error_string.hpp>
#include <mu/io/stream.hpp>
#include <mu/io/tokens.hpp>
#include <mu/llvmc/ast.hpp>
#include <mu/llvmc/availability.hpp>

#include <gc_cpp.h>

mu::llvmc::node_result::~node_result ()
{
    assert (not ((error != nullptr) and (node != nullptr)));
}

mu::llvmc::parser::parser (mu::io::stream <mu::io::token *> & stream_a):
stream (stream_a)
{
    auto error (mapping.map (mu::string (U"function"), &function));
    assert (!error);
}

mu::llvmc::node_result mu::llvmc::module::parse (mu::string const & data_a, mu::llvmc::parser & parser_a)
{
    mu::llvmc::node_result result ({nullptr, nullptr});
    auto module (new (GC) mu::llvmc::ast::module);
    mu::llvmc::scope_set <mu::llvmc::availability::module *> current_module (parser_a.module.current_module, module->availability ());
    auto token (parser_a.stream [0]);
    auto id (token->id ());
    while ((result.node == nullptr) and (result.error == nullptr))
    {
        switch (id)
        {
            case mu::io::token_id::identifier:
            {
                assert (dynamic_cast <mu::io::identifier *> (token) != nullptr);
                auto identifier (static_cast <mu::io::identifier *> (token));
                auto hook (parser_a.mapping.get_hook (identifier->string));
                if (hook.hook != nullptr)
                {
                    parser_a.stream.consume (1);
                    auto node (hook.hook->parse (hook.data, parser_a));
                    if (node.node != nullptr)
                    {
                        auto function (dynamic_cast <mu::llvmc::ast::function *> (node.node));
                        if (function != nullptr)
                        {
                            module->functions.push_back (function);
                        }
                        else
                        {
                            result.error = new (GC) mu::core::error_string (U"Expecting a function");
                        }
                    }
                    else
                    {
                        result.error = node.error;
                    }
                }
                else
                {
                    result.error = new (GC) mu::core::error_string (U"Expecting a keyword");
                }
            }
                break;
            case mu::io::token_id::end:
                result.node = module;
                break;
            default:
                result.error = new (GC) mu::core::error_string (U"Unexpected token");
                break;
        }
        token = parser_a.stream [0];
        id = token->id ();
    }
    return result;
}

bool mu::llvmc::module::covering ()
{
    return false;
}

mu::llvmc::node_result mu::llvmc::function::parse (mu::string const & data_a, mu::llvmc::parser & parser_a)
{
    assert (data_a.empty ());
    mu::llvmc::node_result result ({nullptr, nullptr});
    auto function (new (GC) mu::llvmc::ast::function (parser_a.module.current_module));
    switch (parser_a.stream [0]->id ())
    {
        case mu::io::token_id::identifier:
        {
            parse_name (result, function, parser_a);
            if (result.error == nullptr)
            {
                parse_parameters (result, function, parser_a);
                if (result.error == nullptr)
                {
                    parse_body (result, function, parser_a);
                    if (result.error == nullptr)
                    {
                        parse_results (result, function, parser_a);
                        if (result.error == nullptr)
                        {
                            result.node = function;
                        }
                    }
                }
            }
        }
            break;
        default:
            result.error = new (GC) mu::core::error_string (U"Expecting function name");
            break;
    }
    return result;
}

void mu::llvmc::function::parse_name (mu::llvmc::node_result & result_a, mu::llvmc::ast::function * function_a, mu::llvmc::parser & parser_a)
{
    assert (dynamic_cast <mu::io::identifier *> (parser_a.stream [0]) != nullptr);
    auto name (static_cast <mu::io::identifier *> (parser_a.stream [0]));
    parser_a.stream.consume (1);
    auto error (parser_a.mapping.map (name->string, function_a));
    if (!error)
    {
        function_a->name = name->string;
    }
    else
    {
        result_a.error = new (GC) mu::core::error_string (U"Function name already used");
    }
}

void mu::llvmc::function::parse_parameters (mu::llvmc::node_result & result_a, mu::llvmc::ast::function * function_a, mu::llvmc::parser & parser_a)
{
    auto start_token (parser_a.stream [0]);
    auto start_id (start_token->id ());
    switch (start_id)
    {
        case mu::io::token_id::left_square:
        {
            parser_a.stream.consume (1);
            auto done (false);
            while (result_a.error == nullptr && !done)
            {
                parse_parameter (result_a, function_a, parser_a, done);
            }
        }
            break;
        default:
            result_a.error = new (GC) mu::core::error_string (U"While parsing parameters, expecting left square");
            break;
    }
}

void mu::llvmc::function::parse_parameter (mu::llvmc::node_result & result_a, mu::llvmc::ast::function * function_a, mu::llvmc::parser & parser_a, bool & done_a)
{
    auto next_token (parser_a.stream [0]);
    auto next_id (next_token->id ());
    switch (next_id)
    {
        case mu::io::token_id::identifier:
        {
            parser_a.stream.consume (1);
            assert (dynamic_cast <mu::io::identifier *> (next_token) != nullptr);
            auto identifier (static_cast <mu::io::identifier *> (next_token));
            auto argument (new (GC) mu::llvmc::ast::argument (function_a->entry));
            function_a->parameters.push_back (argument);
            
            
            next_token = parser_a.stream [0];
            next_id = next_token->id ();
        }
            break;
        case mu::io::token_id::right_square:
            parser_a.stream.consume (1);
            done_a = true;
            break;
        default:
            result_a.error = new (GC) mu::core::error_string (U"While parsing parameters, expecting an identifier or right square");
            break;
    }
}

void mu::llvmc::function::parse_body (mu::llvmc::node_result & result_a, mu::llvmc::ast::function * function_a, mu::llvmc::parser & parser_a)
{
    
}

void mu::llvmc::function::parse_results (mu::llvmc::node_result & result_a, mu::llvmc::ast::function * function_a, mu::llvmc::parser & parser_a)
{
    
}

bool mu::llvmc::function::covering ()
{
    return false;
}

mu::llvmc::node_result mu::llvmc::parser::parse ()
{
    auto result (module.parse (mu::string (), *this));
    return result;
}

void mu::llvmc::mapping::refer (mu::string const & identifier_a, boost::function <void (mu::llvmc::ast::node *)> action_a)
{
    auto existing (mappings.find (identifier_a));
    if (existing != mappings.end ())
    {
        action_a (existing->second);
    }
    else
    {
        unresolved.insert (decltype (unresolved)::value_type (identifier_a, action_a));
    }
}

bool mu::llvmc::mapping::map (mu::string const & identifier_a, mu::llvmc::ast::node * node_a)
{
    auto result (false);
    auto existing (mappings.lower_bound (identifier_a));
    if (existing != mappings.end ())
    {
        if (existing->first == identifier_a)
        {
            result = true;
        }
        else
        {
            auto hook (dynamic_cast <mu::llvmc::hook *> (node_a));
            if (hook != nullptr)
            {
                if (hook->covering ())
                {
                    if (identifier_a.compare (0, existing->first.length (), existing->first) == 0)
                    {
                        // Trying to map a keyword that would cover an existing mapping
                        result = true;
                    }
                }
            }            
        }
    }
    if (existing != mappings.begin ())
    {
        --existing;
        if (existing->first.compare (0, existing->first.length (), identifier_a, 0, existing->first.length ()) == 0)
        {
            // Trying to create a mapping that is covered by a keyword
            result = true;
        }
        else
        {
            mappings.insert (existing, decltype (mappings)::value_type (identifier_a, node_a));
        }
    }
    else
    {
        if (!result)
        {
            mappings [identifier_a] = node_a;
        }
    }
    return result;
}

mu::llvmc::hook_result mu::llvmc::mapping::get_hook (mu::string const & identifier_a)
{
    hook_result result ({nullptr, mu::string ()});
    auto existing (mappings.lower_bound (identifier_a));
    mu::llvmc::ast::node * candidate (nullptr);
    mu::string data;
    bool need_covering (false);
    if (existing != mappings.end () && existing->first == identifier_a)
    {
        candidate = existing->second;
    }
    else
    {
        need_covering = true;
        if (existing != mappings.begin ())
        {
            --existing;
            auto data_position (existing->first.length ());
            if (identifier_a.compare (0, data_position, existing->first) == 0)
            {
                data.append (identifier_a.begin () + data_position, identifier_a.end ());
                candidate = existing->second;
            }
        }
    }
    if (candidate != nullptr)        
    {
        auto hook (dynamic_cast <mu::llvmc::hook *> (candidate));
        if (hook != nullptr)
        {
            if (need_covering)
            {
                if (hook->covering ())
                {
                    result.data.swap (data);
                    result.hook = hook;
                }
            }
            else
            {
                result.hook = hook;
            }
        }
    }
    return result;
}