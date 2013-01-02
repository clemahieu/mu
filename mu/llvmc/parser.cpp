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

mu::llvmc::node_result mu::llvmc::parser::parse ()
{
    mu::llvmc::node_result result ({nullptr, nullptr});
    auto module (new (GC) mu::llvmc::ast::module);
    auto token (stream [0]);
    auto id (token->id ());
    while ((result.node == nullptr) and (result.error == nullptr))
    {
        switch (id)
        {
            case mu::io::token_id::identifier:
            {
                assert (dynamic_cast <mu::io::identifier *> (token) != nullptr);
                auto identifier (static_cast <mu::io::identifier *> (token));
                auto keyword (mapping.get_keyword (identifier->string));
                if (keyword != nullptr)
                {
                    auto node (keyword->parse (stream));
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
    if (existing->first == identifier_a)
    {
        result = true;
    }
    else
    {
        if (existing != mappings.begin ())
        {
            --existing;
            mappings.insert (existing, decltype (mappings)::value_type (identifier_a, node_a));
        }
        else
        {
            mappings [identifier_a] = node_a;                
        }
    }
    return result;
}

mu::llvmc::keyword * mu::llvmc::mapping::get_keyword (mu::string const & identifier_a)
{
    mu::llvmc::keyword * result (nullptr);
    auto existing (mappings.lower_bound (identifier_a));
    mu::llvmc::ast::node * candidate (nullptr);
    auto needs_dominator (false);
    if (existing != mappings.end () && existing->first == identifier_a)
    {
        candidate = existing->second;
    }
    else
    {
        needs_dominator = true;
        if (existing != mappings.begin ())
        {
            --existing;
            if (identifier_a.compare (0, existing->first.length (), existing->first) == 0)
            {
                candidate = existing->second;
            }
        }
    }
    if (candidate != nullptr)        
    {
        auto keyword (dynamic_cast <mu::llvmc::keyword *> (candidate));
        if (keyword != nullptr)
        {
            if (needs_dominator)
            {
                if (keyword->dominator())
                {
                    result = keyword;
                }
            }
            else
            {
                result = keyword;
            }
        }
    }
    return result;
}