#include <mu/llvmc/parser.hpp>

#include <boost/lexical_cast.hpp>

#include <mu/core/error_string.hpp>
#include <mu/io/stream.hpp>
#include <mu/io/tokens.hpp>
#include <mu/llvmc/ast.hpp>
#include <mu/llvmc/availability.hpp>
#include <mu/llvmc/partial_ast.hpp>
#include <mu/llvmc/wrapper.hpp>

#include <llvm/Type.h>

#include <gc_cpp.h>

mu::llvmc::parser::parser (mu::llvmc::partial_ast & stream_a):
current_mapping (&globals),
stream (stream_a)
{
    auto error1 (keywords.insert (mu::string (U"function"), &function));
    assert (!error1);
    auto error2 (keywords.insert (mu::string (U"int"), &int_type));
    assert (!error2);
    auto error3 (keywords.insert (mu::string (U"set"), &set_hook));
    assert (!error3);
    auto error4 (keywords.insert (mu::string (U"if"), &if_hook));
    assert (!error4);
}

mu::llvmc::node_result mu::llvmc::module::parse (mu::string const & data_a, mu::llvmc::parser & parser_a)
{
    mu::llvmc::node_result result ({nullptr, nullptr});
    auto module (new (GC) mu::llvmc::ast::module);
    auto previous_availability (parser_a.current_availability);
    auto new_availability (new (GC) mu::llvmc::availability::module);
    parser_a.current_availability = new_availability;
    new_availability->parent = previous_availability;
    while ((result.node == nullptr) and (result.error == nullptr))
    {
        auto item (parser_a.stream.peek ());
        if (item.ast != nullptr)
        {
            auto function (dynamic_cast <mu::llvmc::ast::function *> (item.ast));
            if (function != nullptr)
            {
                parser_a.stream.consume ();
                module->functions.push_back (function);
            }
            else
            {
                result.error = new (GC) mu::core::error_string (U"Expecting a function");
            }        
        }
        else if (item.token != nullptr)
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
        else
        {
            result.error = item.error;
        }
    }
    parser_a.current_availability = previous_availability;
    return result;
}

bool mu::llvmc::module::covering ()
{
    return false;
}

mu::llvmc::node_result mu::llvmc::function_hook::parse (mu::string const & data_a, mu::llvmc::parser & parser_a)
{
    mu::llvmc::function parser_l (data_a, parser_a);
    auto previous_availability (parser_a.current_availability);
    auto new_availability (new (GC) mu::llvmc::availability::function);
    new_availability->parent = previous_availability;
    parser_a.current_availability = new_availability;
    auto previous_mapping (parser_a.current_mapping);
    parser_a.current_mapping = &parser_l.block;
    parser_l.parse ();
    parser_a.current_availability = previous_availability;
    parser_a.current_mapping = previous_mapping;
    return parser_l.result;
}

mu::llvmc::function::function (mu::string const & data_a, mu::llvmc::parser & parser_a):
block (parser_a.current_mapping),
result ({nullptr, nullptr}),
function_m (new (GC) mu::llvmc::ast::function (parser_a.module.current_module)),
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
    parser.stream.consume ();
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
    if (parser.stream.peek ().token != nullptr)
    {
        auto id (parser.stream.peek ().token->id ());
        switch (id)
        {
            case mu::io::token_id::identifier:
            {
                auto name (static_cast <mu::io::identifier *> (parser.stream.peek ().token));
                parser.stream.consume ();
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
    if (parser.stream.peek ().token != nullptr)
    {
        auto start_token (parser.stream.peek ().token);
        auto start_id (start_token->id ());
        switch (start_id)
        {
            case mu::io::token_id::left_square:
            {
                parser.stream.consume ();
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
    auto node (parser.stream.peek ());
    if (node.ast != nullptr)
    {
        auto type (dynamic_cast <mu::llvmc::wrapper::type *> (parser.stream.peek ().ast));
        if (type != nullptr)
        {
            parser.stream.consume ();
            if (parser.stream.peek ().token != nullptr)
            {
                auto next_token (parser.stream.peek ().token);
                auto next_id (next_token->id ());
                switch (next_id)
                {
                    case mu::io::token_id::identifier:
                    {
                        parser.stream.consume ();
                        auto identifier (static_cast <mu::io::identifier *> (next_token));
                        auto argument (new (GC) mu::llvmc::ast::argument (type, function_m->entry));
                        function_m->parameters.push_back (argument);
                        if (block.insert (identifier->string, argument))
                        {
                            result.error = new (GC) mu::core::error_string (U"Unable to use identifier");
                        }
                    }
                        break;
                    default:
                        result.error = new (GC) mu::core::error_string (U"While parsing parameters, expecting an identifier");
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
    else if (node.token != nullptr)
    {
        auto id (parser.stream.peek ().token->id ());
        switch (id)
        {
            case mu::io::token_id::right_square:
                parser.stream.consume ();
                done_a = true;
                break;
            default:
                result.error = new (GC) mu::core::error_string (U"Expecting type or right square");
                break;                
        }
    }
    else
    {
        result.error = node.error;
    }
}

void mu::llvmc::function::parse_body ()
{
    auto opening (parser.stream.peek ());
    if (opening.token != nullptr)
    {
        auto opening_id (opening.token->id ());
        switch (opening_id)
        {
            case mu::io::token_id::left_square:
            {
                parser.stream.consume ();
                auto done (false);
                while (!done && result.error == nullptr)
                {
                    auto next (parser.stream.peek ());
                    if (next.ast != nullptr)
                    {
                        auto expression (dynamic_cast <mu::llvmc::ast::expression *> (next.ast));
                        if (expression != nullptr)
                        {
                            parser.stream.consume ();
                            function_m->roots.push_back (expression);
                        }
                        else
                        {
                            result.error = new (GC) mu::core::error_string (U"Expecting expression");
                        }
                    }
                    else if (next.token != nullptr)
                    {
                        auto next_id (next.token->id ());
                        switch (next_id)
                        {
                            case mu::io::token_id::right_square:
                                parser.stream.consume ();
                                done = true;
                                break;
                            case mu::io::token_id::left_square:
                            {
                                mu::llvmc::expression expression_l (parser);
                                expression_l.parse ();
                                if (expression_l.result.node != nullptr)
                                {
                                    assert (dynamic_cast <mu::llvmc::ast::expression *> (expression_l.result.node));
                                    function_m->roots.push_back (static_cast <mu::llvmc::ast::expression *> (expression_l.result.node));
                                    parser.stream.consume ();
                                    next = parser.stream.peek ();
                                }
                                else
                                {
                                    result.error = expression_l.result.error;
                                }
                            }
                                break;
                            default:
                                result.error = new (GC) mu::core::error_string (U"Expecting right square");
                                break;
                        }
                    }
                    else
                    {
                        result.error = new (GC) mu::core::error_string (U"Expecting function end");
                    }
                }
            }
                break;
            default:
                result.error = new (GC) mu::core::error_string (U"Expecting left square");
                break;
        }
    }
    else
    {
        result.error = new (GC) mu::core::error_string (U"Expecting function body");
    }
}

void mu::llvmc::function::parse_results ()
{
    auto opening (parser.stream.peek ());
    if (opening.token != nullptr)
    {
        auto opening_id (opening.token->id ());
        switch (opening_id)
        {
            case mu::io::token_id::left_square:
            {
                parser.stream.consume ();
                auto next (parser.stream.peek ());
                auto done (false);
                while (result.error == nullptr && !done)
                {
                    if (next.token != nullptr)
                    {
                        auto next_id (next.token->id ());
                        switch (next_id)
                        {
                            case mu::io::token_id::left_square:
                                parser.stream.consume ();
                                parse_result_set ();
                                next = parser.stream.peek ();
                                break;
                            case mu::io::token_id::right_square:
                                done = true;
                                break;
                            default:
                                result.error = new (GC) mu::core::error_string (U"Expecting identifier or right square");
                                break;
                        }
                    }
                    else
                    {
                        result.error = new (GC) mu::core::error_string (U"Expecting results end");
                    }
                }
            }
                break;
            default:
                result.error = new (GC) mu::core::error_string (U"Expecting left square");
                break;
        }
    }
    else
    {
        result.error = new (GC) mu::core::error_string (U"Expecting results list");
    }
}

void mu::llvmc::function::parse_result_set ()
{
    auto index (function_m->results.size ());
    function_m->results.push_back (decltype (function_m->results)::value_type ());
    auto node (parser.stream.peek ());
    auto done (false);
    while (result.error == nullptr && !done)
    {
        if (node.ast != nullptr)
        {
            auto type (dynamic_cast <mu::llvmc::wrapper::type *> (node.ast));
            if (type != nullptr)
            {
                parser.stream.consume ();
                auto next (parser.stream.peek ());
                auto next_id (next.token->id ());
                switch (next_id)
                {
                    case mu::io::token_id::identifier:
                    {
                        parser.stream.consume ();
                        auto result (new (GC) mu::llvmc::ast::result (type));
                        function_m->results [index].push_back (result);
                        block.refer (static_cast <mu::io::identifier *> (next.token)->string,
                                     [result]
                                     (mu::llvmc::ast::node * node_a)
                                     {
                                         auto scoped (dynamic_cast <mu::llvmc::ast::scoped *> (node_a));
                                         result->value = scoped;
                                     });
                        node = parser.stream.peek ();
                    }
                        break;
                    default:
                        result.error = new (GC) mu::core::error_string (U"Expecting identifier");
                        break;
                }
            }
            else
            {
                result.error = new (GC) mu::core::error_string (U"Expecting a type");
            }
        }
        else if (node.token != nullptr)
        {
            auto node_id (node.token->id ());
            switch (node_id)
            {
                case mu::io::token_id::right_square:
                    parser.stream.consume ();
                    done = true;
                    break;
                default:
                    result.error = new (GC) mu::core::error_string (U"Expecting right_square");
                    break;
            }
        }
        else
        {
            result.error = node.error;
        }
    }
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
    return result;
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
    auto result (existing == mappings.end ());
    if (result)
    {
        result = parent->get (name_a, action_a);
        if (result)
        {
            unresolved.insert (decltype (unresolved)::value_type (name_a, action_a));
        }
    }
    else
    {
        action_a (existing->second);
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

mu::llvmc::node_result mu::llvmc::int_type::parse (mu::string const & data_a, mu::llvmc::parser & parser_a)
{
    mu::llvmc::node_result result ({nullptr, nullptr});
    try
    {
        unsigned int bits (boost::lexical_cast <unsigned int> (data_a));
        if (bits <= 1024)
        {
            result.node = new (GC) mu::llvmc::wrapper::integer_type (&parser_a.availability, llvm::Type::getIntNTy (parser_a.context, bits));
        }
        else
        {
            result.error = new (GC) mu::core::error_string (U"Bit width too wide");
        }
    }
    catch (boost::bad_lexical_cast)
    {
        result.error = new (GC) mu::core::error_string (U"Unable to convert number to unsigned integer");
    }
    return result;
}

bool mu::llvmc::int_type::covering ()
{
    return true;
}

mu::llvmc::expression::expression (mu::llvmc::parser & parser_a):
result ({nullptr, nullptr}),
parser (parser_a)
{
}

void mu::llvmc::expression::parse ()
{
    auto expression_l (new (GC) mu::llvmc::ast::definite_expression (parser.current_availability));
    auto node (parser.stream.peek ());
    if (node.token != nullptr)
    {
        auto node_id (node.token->id ());
        switch (node_id)
        {
            case mu::io::token_id::left_square:
            {
                parser.stream.consume ();
                auto done (false);
                while (!done && result.error == nullptr)
                {
                    auto next (parser.stream.peek ());
                    if (next.ast != nullptr)
                    {
                        expression_l->arguments.push_back (next.ast);
                    }
                    else if (next.token != nullptr)
                    {
                        auto next_id (next.token->id ());
                        switch (next_id)
                        {
                            case mu::io::token_id::identifier:
                            {
                                parser.stream.consume ();
                                auto & arguments (expression_l->arguments);
                                auto position (expression_l->arguments.size ());
                                expression_l->arguments.push_back (nullptr);
                                parser.current_mapping->refer(static_cast <mu::io::identifier *> (next.token)->string,
                                            [&arguments, position]
                                            (mu::llvmc::ast::node * node_a)
                                            {
                                                arguments [position] = node_a;
                                            });
                            }
                                break;
                            case mu::io::token_id::left_square:
                            {
                                mu::llvmc::expression expression_p (parser);
                                expression_p.parse ();
                                if (expression_p.result.node != nullptr)
                                {
                                    expression_l->arguments.push_back (expression_p.result.node);
                                }
                                else
                                {
                                    result.error = expression_p.result.error;
                                }
                            }
                                break;
                            case mu::io::token_id::right_square:
                                done = true;
                                break;
                            default:
                                result.error = new (GC) mu::core::error_string (U"");
                                break;
                        }
                    }
                    else
                    {
                        result.error = new (GC) mu::core::error_string (U"");
                    }
                }
            }
                break;
            default:
                result.error = new (GC) mu::core::error_string (U"Expecting left square");
                break;
        }
    }
    else if (node.ast != nullptr)
    {
        result.error = new (GC) mu::core::error_string (U"Expecting token");
    }
    else
    {
        result.error = node.error;
    }
    if (result.error == nullptr)
    {
        result.node = expression_l;
    }
}

mu::llvmc::node_result mu::llvmc::set_hook::parse (mu::string const & data_a, mu::llvmc::parser & parser_a)
{
    assert (data_a.empty ());
    mu::llvmc::node_result result ({nullptr, nullptr});
    parser_a.stream.consume ();
    auto name (parser_a.stream.peek());
    if (name.token != nullptr)
    {
        auto name_id (name.token->id ());
        switch (name_id)
        {
            case mu::io::token_id::identifier:
            {
                parser_a.stream.consume ();
                auto next (parser_a.stream.peek ());
                if (next.token != nullptr)
                {
                    auto next_id (next.token->id ());
                    switch (next_id)
                    {
                        case mu::io::token_id::left_square:
                        {
                            mu::llvmc::expression expression (parser_a);
                            expression.parse ();
                            if (expression.result.node != nullptr)
                            {
                                auto error (parser_a.current_mapping->insert(static_cast <mu::io::identifier *> (name.token)->string, expression.result.node));
                                if (error)
                                {
                                    result.error = new (GC) mu::core::error_string (U"Unable to use name");
                                }
                                else
                                {
                                    result.node = expression.result.node;
                                }
                            }
                            else
                            {
                                result.error = expression.result.error;
                            }
                        }
                            break;
                        default:
                            result.error = new (GC) mu::core::error_string (U"Expecting expressing");
                            break;
                    }
                }
                else if (next.ast != nullptr)
                {
                    result.error = new (GC) mu::core::error_string (U"Expecting an expression");
                }
                else
                {
                    result.error = next.error;
                }
            }
                break;
            default:
                result.error = new (GC) mu::core::error_string (U"Expecting identifier");
                break;
        }
    }
    else if (name.ast != nullptr)
    {
        result.error = new (GC) mu::core::error_string (U"Expecting a name");
    }
    else
    {
        result.error = name.error;
    }
    return result;
}

bool mu::llvmc::set_hook::covering ()
{
    return false;
}

bool mu::llvmc::global::insert (mu::string const & identifier_a, mu::llvmc::ast::node * node_a)
{
    auto hook (keywords->get_hook (identifier_a));
    auto result (hook.hook != nullptr);
    if (!result)
    {
        auto existing (mappings.lower_bound (identifier_a));
        result = (existing != mappings.end ()) && (existing->first == identifier_a);
        if (!result)
        {
            if (existing != mappings.begin())
            {
                --existing;
            }
            mappings.insert (existing, decltype (mappings)::value_type (identifier_a, node_a));
        }
    }
    return result;
}

mu::llvmc::node_result mu::llvmc::if_hook::parse (mu::string const & data_a, mu::llvmc::parser & parser_a)
{
    mu::llvmc::node_result result;
    auto previous_availability (parser_a.current_availability);
    auto expression (new (GC) mu::llvmc::ast::if_expression (previous_availability));
    auto true_availability (new (GC) mu::llvmc::availability::if_branch);
    parser_a.current_availability = true_availability;
    result.error = parse_branch (parser_a, expression->true_roots);
    if (result.error == nullptr)
    {
        auto false_availability (new (GC) mu::llvmc::availability::if_branch);
        parser_a.current_availability = false_availability;
        result.error = parse_branch (parser_a, expression->false_roots);
    }
    if (result.error == nullptr)
    {
        result.node = expression;
    }
    parser_a.current_availability = previous_availability;
    return result;
}

mu::core::error * mu::llvmc::if_hook::parse_branch (mu::llvmc::parser & parser_a, mu::vector <mu::llvmc::ast::expression *> & target)
{
    mu::core::error * result (nullptr);
    auto opening (parser_a.stream.peek ());
    if (opening.token != nullptr)
    {
        auto opening_id (opening.token->id ());
        switch (opening_id)
        {
            case mu::io::token_id::left_square:
            {
                parser_a.stream.consume ();
                auto done (false);
                while (!done)
                {
                    auto next (parser_a.stream.peek ());
                    if (next.ast != nullptr)
                    {
                        auto expression_l (dynamic_cast <mu::llvmc::ast::expression *> (next.ast));
                        if (expression_l != nullptr)
                        {
                            target.push_back (expression_l);
                        }
                        else
                        {
                            result = new (GC) mu::core::error_string (U"Expecting expression");
                        }
                    }
                    else if (next.token != nullptr)
                    {
                        auto next_id (next.token->id ());
                        switch (next_id)
                        {
                            case mu::io::token_id::left_square:
                            {
                                mu::llvmc::expression expression_l (parser_a);
                                expression_l.parse ();                                
                            }
                                break;
                            case mu::io::token_id::right_square:
                                done = true;
                                break;
                            default:
                                result = new (GC) mu::core::error_string (U"Expecting expression or end of block");
                                break;
                        }
                    }
                    else
                    {
                        result = next.error;
                    }
                }
            }
                break;
            default:
                result = new (GC) mu::core::error_string (U"Expecting left square");
                break;
        }
    }
    else if (opening.ast != nullptr)
    {
        result = new (GC) mu::core::error_string (U"Expecting block");
    }
    else
    {
        result = opening.error;
    }
}

bool mu::llvmc::if_hook::covering ()
{
    return false;
}