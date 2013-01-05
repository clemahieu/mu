#include <mu/llvmc/parser.hpp>

#include <mu/core/error_string.hpp>
#include <mu/io/stream.hpp>
#include <mu/io/tokens.hpp>
#include <mu/llvmc/ast.hpp>
#include <mu/llvmc/availability.hpp>
#include <mu/llvmc/stream_partial_ast.hpp>
#include <mu/llvmc/wrapper.hpp>

#include <gc_cpp.h>

mu::llvmc::node_result::~node_result ()
{
    assert (not ((error != nullptr) and (node != nullptr)));
}

mu::llvmc::parser::parser (mu::llvmc::stream_partial_ast & stream_a):
current_mapping (&globals),
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
    while ((result.node == nullptr) and (result.error == nullptr))
    {
        auto item (parser_a.stream [0]);
        if (item.ast != nullptr)
        {
            auto function (dynamic_cast <mu::llvmc::ast::function *> (item.ast));
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
            auto id (item.token->id ());
            switch (id)
            {
                case mu::io::token_id::end:
                    result.node = module;
                    break;
                default:                    
                    result.error = new (GC) mu::core::error_string (U"Expecting function or end of stream");
                    break;
            }
        }
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
block (parser_a.current_mapping),
result ({nullptr, nullptr}),
function_m (new (GC) mu::llvmc::ast::function (parser.module.current_module)),
parser (parser_a)
{
    assert (data_a.empty ());
}

mu::llvmc::function::~function ()
{
    parser.current_mapping = block.parent;
}

void mu::llvmc::function::parse ()
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

void mu::llvmc::function::parse_name ()
{
    if (parser.stream [0].token != nullptr)
    {
        auto id (parser.stream [0].token->id ());
        switch (id)
        {
            case mu::io::token_id::identifier:
            {
                auto name (static_cast <mu::io::identifier *> (parser.stream [0].token));
                parser.stream.consume (1);
                auto error (block.parent->reserve (name->string));
                if (!error)
                {
                    assert (block.mappings.find (name->string) == block.mappings.end ());
                    block.mappings.insert (decltype (block.mappings)::value_type (name->string, function_m));
                    function_m->name = name->string;
                }
                else
                {
                    result.error = new (GC) mu::core::error_string (U"Function name already used");
                }
            }
                break;
            default:
                result.error = new (GC) mu::core::error_string (U"Expecting identifier");
                break;
        }
    }
    else
    {
        result.error = new (GC) mu::core::error_string (U"Expecting function name");
    }
}

void mu::llvmc::function::parse_parameters ()
{
    if (parser.stream [0].token != nullptr)
    {
        auto start_token (parser.stream [0].token);
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
    else
    {
        result.error = new (GC) mu::core::error_string (U"Expecting parameters list");
    }
}

void mu::llvmc::function::parse_parameter (bool & done_a)
{
    if (parser.stream [0].ast != nullptr)
    {
        auto type (dynamic_cast <mu::llvmc::wrapper::type *> (parser.stream [0].ast));
        if (type != nullptr)
        {
            parser.stream.consume (1);
            if (parser.stream [0].token != nullptr)
            {
                auto next_token (parser.stream [0].token);
                auto next_id (next_token->id ());
                switch (next_id)
                {
                    case mu::io::token_id::identifier:
                    {
                        parser.stream.consume (1);
                        auto identifier (static_cast <mu::io::identifier *> (next_token));
                        auto argument (new (GC) mu::llvmc::ast::argument (function_m->entry));
                        function_m->parameters.push_back (argument);
                        if (block.insert (identifier->string, argument))
                        {
                            result.error = new (GC) mu::core::error_string (U"Unable to use identifier");
                        }
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
            else
            {
                result.error = new (GC) mu::core::error_string (U"Expecting a parameter name");
            }
        }
        else
        {
            result.error = new (GC) mu::core::error_string (U"Not a type");
        }
    }
    else
    {
        result.error = new (GC) mu::core::error_string (U"Expecting type");
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
    auto existing (mappings.lower_bound (identifier_a));
    if (hook_a->covering () && existing != mappings.end ())
    {
        auto size (identifier_a.length ());
        result = existing->first.compare (0, size, identifier_a, 0, size) == 0;
    }
    if (existing != mappings.begin ())
    {
        --existing;
        if (existing->second->covering ())
        {
            auto size (existing->first.length ());
            result = result || existing->first.compare (0, size, identifier_a, 0, size) == 0;
        }
    }
    if (!result)
    {
        mappings.insert (existing, decltype (mappings)::value_type (identifier_a, hook_a));
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

mu::llvmc::block::block (mu::llvmc::mapping * parent_a):
parent (parent_a)
{
}

bool mu::llvmc::block::insert (mu::string const & name_a, mu::llvmc::ast::node * node_a)
{
    auto result (parent->reserve (name_a));
    if (!result)
    {
        auto existing (mappings.lower_bound (name_a));
        result = (existing != mappings.end ()) && (existing->first == name_a);
        if (!result)
        {
            if (existing != mappings.begin())
            {
                --existing;
            }
            mappings.insert (existing, decltype (mappings)::value_type (name_a, node_a));
        }
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