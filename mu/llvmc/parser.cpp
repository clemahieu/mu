#include <mu/llvmc/parser.hpp>

#include <mu/core/error_string.hpp>
#include <mu/io/stream.hpp>
#include <mu/io/tokens.hpp>
#include <mu/llvmc/ast.hpp>

#include <gc_cpp.h>

mu::llvmc::node_result::~node_result ()
{
    assert (not ((error != nullptr) and (node != nullptr)));
}

mu::llvmc::parser::parser (mu::io::stream <mu::io::token *> & stream_a):
stream (stream_a)
{
}

mu::llvmc::node_result mu::llvmc::module::parse (mu::string const & data_a, mu::llvmc::mapping & mapping, mu::io::stream <mu::io::token *> & stream_a)
{
    mu::llvmc::node_result result ({nullptr, nullptr});
    auto module (new (GC) mu::llvmc::ast::module);
    auto token (stream_a [0]);
    auto id (token->id ());
    while ((result.node == nullptr) and (result.error == nullptr))
    {
        switch (id)
        {
            case mu::io::token_id::identifier:
            {
                assert (dynamic_cast <mu::io::identifier *> (token) != nullptr);
                auto identifier (static_cast <mu::io::identifier *> (token));
                auto hook (mapping.get_hook (identifier->string));
                if (hook.hook != nullptr)
                {
                    auto node (hook.hook->parse (hook.data, mapping, stream_a));
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
    }
    return result;
}

bool mu::llvmc::module::covering ()
{
    return false;
}


mu::llvmc::node_result mu::llvmc::function::parse (mu::string const & data_a, mu::llvmc::mapping & mapping, mu::io::stream <mu::io::token *> & stream_a)
{
    mu::llvmc::node_result result ({nullptr, nullptr});
    return result;
}

bool mu::llvmc::function::covering ()
{
    return false;
}

mu::llvmc::node_result mu::llvmc::parser::parse ()
{
    auto result (module.parse (mu::string (), mapping, stream));
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