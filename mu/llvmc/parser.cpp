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
    auto error (keywords.insert (mu::string (U"function"), &function));
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
                auto hook (parser_a.keywords.get_hook (identifier->string));
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

mu::llvmc::node_result mu::llvmc::function_hook::parse (mu::string const & data_a, mu::llvmc::parser & parser_a)
{
    mu::llvmc::function parser_l (data_a, parser_a);
    parser_l.parse ();
    return parser_l.result;
}

mu::llvmc::function::function (mu::string const & data_a, mu::llvmc::parser & parser_a):
result ({nullptr, nullptr}),
function_m (new (GC) mu::llvmc::ast::function (parser.module.current_module)),
data (data_a),
parser (parser_a)
{
}

void mu::llvmc::function::parse ()
{
    assert (data.empty ());
    switch (parser.stream [0]->id ())
    {
        case mu::io::token_id::identifier:
        {
            parse_name ();
            if (result.error == nullptr)
            {
                parse_parameters ();
                if (result.error == nullptr)
                {
                    parse_body ();
                    if (result.error == nullptr)
                    {
                        parse_results ();
                        if (result.error == nullptr)
                        {
                            result.node = function_m;
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
}

void mu::llvmc::function::parse_name ()
{
    assert (dynamic_cast <mu::io::identifier *> (parser.stream [0]) != nullptr);
    auto name (static_cast <mu::io::identifier *> (parser.stream [0]));
    parser.stream.consume (1);
    auto error (block.parent->reserve (name->string));
    if (!error)
    {
        function_m->name = name->string;
    }
    else
    {
        result.error = new (GC) mu::core::error_string (U"Function name already used");
    }
}

void mu::llvmc::function::parse_parameters ()
{
    auto start_token (parser.stream [0]);
    auto start_id (start_token->id ());
    switch (start_id)
    {
        case mu::io::token_id::left_square:
        {
            parser.stream.consume (1);
            auto done (false);
            while (result.error == nullptr && !done)
            {
                parse_parameter (done);
            }
        }
            break;
        default:
            result.error = new (GC) mu::core::error_string (U"While parsing parameters, expecting left square");
            break;
    }
}

void mu::llvmc::function::parse_parameter (bool & done_a)
{
    auto next_token (parser.stream [0]);
    auto next_id (next_token->id ());
    switch (next_id)
    {
        case mu::io::token_id::identifier:
        {
            parser.stream.consume (1);
            assert (dynamic_cast <mu::io::identifier *> (next_token) != nullptr);
            auto identifier (static_cast <mu::io::identifier *> (next_token));
            auto argument (new (GC) mu::llvmc::ast::argument (function_m->entry));
            function_m->parameters.push_back (argument);
            
            
            next_token = parser.stream [0];
            next_id = next_token->id ();
        }
            break;
        case mu::io::token_id::right_square:
            parser.stream.consume (1);
            done_a = true;
            break;
        default:
            result.error = new (GC) mu::core::error_string (U"While parsing parameters, expecting an identifier or right square");
            break;
    }
}

void mu::llvmc::function::parse_body ()
{
    
}

void mu::llvmc::function::parse_results ()
{
    
}

bool mu::llvmc::function_hook::covering ()
{
    return false;
}

mu::llvmc::node_result mu::llvmc::parser::parse ()
{
    auto result (module.parse (mu::string (), *this));
    return result;
}

bool mu::llvmc::keywords::insert (mu::string const & identifier_a, mu::llvmc::hook * hook_a)
{
    auto result (false);
    auto existing (get_hook (identifier_a));
    if (existing.hook == nullptr)
    {
        mappings [identifier_a] = hook_a;
    }
    else
    {
        result = true;
    }
    return result;
}

mu::llvmc::hook_result mu::llvmc::keywords::get_hook (mu::string const & identifier_a)
{
    hook_result result ({nullptr, mu::string ()});
    auto existing (mappings.lower_bound (identifier_a));
    mu::llvmc::hook * candidate (nullptr);
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
        if (need_covering)
        {
            if (candidate->covering ())
            {
                result.data.swap (data);
                result.hook = candidate;
            }
        }
        else
        {
            result.hook = candidate;
        }
    }
    return result;
}

bool mu::llvmc::global::reserve (mu::string const & name_a)
{
    auto existing (mappings.find(name_a));
    auto result (existing != mappings.end ());
    if (result)
    {
        auto hook (keywords->get_hook (name_a));
        result = hook.hook != nullptr;
    }
    return result;
}

bool mu::llvmc::global::get (mu::string const & name_a, boost::function <void (mu::llvmc::ast::node *)> action_a)
{
    auto existing (mappings.find (name_a));
    auto result (existing == mappings.end ());
    if (!result)
    {
        action_a (existing->second);
    }
    return result;
}

void mu::llvmc::global::refer (mu::string const & name_a, boost::function <void (mu::llvmc::ast::node *)> action_a)
{
    auto error (get (name_a, action_a));
    if (error)
    {
        unresolved.insert (decltype (unresolved)::value_type (name_a, action_a));
    }
}

bool mu::llvmc::block::reserve (mu::string const & name_a)
{
    auto result (parent->reserve (name_a));
    if (!result)
    {
        auto existing (mappings.find (name_a));
        result = existing != mappings.end ();
        mappings [name_a] = nullptr;
    }
    return result;
}

bool mu::llvmc::block::get (mu::string const & name_a, boost::function <void (mu::llvmc::ast::node *)> action_a)
{
    auto existing (mappings.find (name_a));
    auto result (existing != mappings.end ());
    if (result)
    {
        result = parent->get (name_a, action_a);
    }
    else
    {
        action_a (existing->second);
    }
    return result;
}

void mu::llvmc::block::refer (mu::string const & name_a, boost::function <void (mu::llvmc::ast::node *)> action_a)
{
    auto existing (mappings.find (name_a));
    auto result (existing != mappings.end ());
    if (result)
    {
        result = parent->get (name_a, action_a);
        if (result)
        {
            unresolved.insert (decltype (unresolved)::value_type (name_a, action_a));
        }
    }
}

void mu::llvmc::block::accept (mu::multimap <mu::string, boost::function <void (mu::llvmc::ast::node *)>> unresolved_a)
{
    unresolved.insert (unresolved_a.begin (), unresolved_a.end ());
}

void mu::llvmc::global::accept (mu::multimap <mu::string, boost::function <void (mu::llvmc::ast::node *)>> unresolved_a)
{
    unresolved.insert (unresolved_a.begin (), unresolved_a.end ());
}