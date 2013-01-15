#include <mu/llvmc/parser.hpp>

#include <boost/lexical_cast.hpp>

#include <mu/core/error_string.hpp>
#include <mu/io/stream.hpp>
#include <mu/io/tokens.hpp>
#include <mu/llvmc/ast.hpp>
#include <mu/llvmc/availability.hpp>
#include <mu/llvmc/partial_ast.hpp>
#include <mu/llvmc/wrapper.hpp>
#include <mu/io/stream_token.hpp>

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
    auto error5 (keywords.insert (mu::string (U"loop"), &loop_hook));
    assert (!error5);
}

mu::llvmc::node_result mu::llvmc::module::parse (mu::string const & data_a, mu::llvmc::parser & parser_a)
{
    mu::llvmc::node_result result ({nullptr, nullptr});
    auto module (new (GC) mu::llvmc::ast::module);
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
    return result;
}

bool mu::llvmc::module::covering ()
{
    return false;
}

mu::llvmc::node_result mu::llvmc::function_hook::parse (mu::string const & data_a, mu::llvmc::parser & parser_a)
{
    mu::llvmc::function parser_l (data_a, parser_a);
    auto previous_mapping (parser_a.current_mapping);
    parser_a.current_mapping = &parser_l.block;
    parser_l.parse ();
    parser_a.current_mapping = previous_mapping;
    return parser_l.result;
}

mu::llvmc::function::function (mu::string const & data_a, mu::llvmc::parser & parser_a):
block (parser_a.current_mapping),
result ({nullptr, nullptr}),
function_m (new (GC) mu::llvmc::ast::function),
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
    switch (parser.stream.tokens [0]->id ())
    {
        case mu::io::token_id::left_square:
        {
            parser.stream.tokens.consume (1);
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
                        auto argument (new (GC) mu::llvmc::ast::argument (type));
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
    switch (parser.stream.tokens [0]->id ())
    {
        case mu::io::token_id::left_square:
        {
            parser.stream.tokens.consume (1);
            auto done (false);
            while (!done && result.error == nullptr)
            {
                switch (parser.stream.tokens [0]->id ())
                {
                    case mu::io::token_id::right_square:
                        parser.stream.tokens.consume (1);
                        done = true;
                        break;
                    default:
                    {
                        auto next (parser.stream.peek ());
                        if (next.ast != nullptr)
                        {
                            parser.stream.consume ();
                            function_m->roots.push_back (next.ast);
                        }
                        else if (next.token != nullptr)
                        {
                            result.error = new (GC) mu::core::error_string (U"Expecting expression");
                        }
                        else
                        {
                            result.error = next.error;
                        }
                    }
                        break;
                }
            }
        }
            break;
        default:
            result.error = new (GC) mu::core::error_string (U"Expecting left square");
            break;
    }
}

void mu::llvmc::function::parse_results ()
{
    switch (parser.stream.tokens [0]->id ())
    {
        case mu::io::token_id::left_square:
        {
            parser.stream.tokens.consume (1);
            auto next (parser.stream.tokens [0]);
            auto done (false);
            while (result.error == nullptr && !done)
            {
                switch (next->id ())
                {
                    case mu::io::token_id::left_square:
                        parser.stream.tokens.consume (1);
                        parse_result_set ();
                        next = parser.stream.tokens [0];
                        break;
                    case mu::io::token_id::right_square:
                        done = true;
                        break;
                    default:
                        result.error = new (GC) mu::core::error_string (U"Expecting identifier or right square");
                        break;
                }
            }
        }
            break;
        default:
            result.error = new (GC) mu::core::error_string (U"Expecting left square");
            break;
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
                if (next.token != nullptr)
                {
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
                                             result->value = node_a;
                                         });
                            node = parser.stream.peek ();
                        }
                            break;
                        default:
                            result.error = new (GC) mu::core::error_string (U"Expecting identifier");
                            break;
                    }
                }
                else if (next.ast != nullptr)
                {
                    result.error = new (GC) mu::core::error_string (U"Expecting result reference");
                }
                else
                {
                    result.error = next.error;
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
            result.node = new (GC) mu::llvmc::wrapper::integer_type (llvm::Type::getIntNTy (parser_a.context, bits));
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
    auto expression_l (new (GC) mu::llvmc::ast::definite_expression);
    switch (parser.stream.tokens [0]->id ())
    {
        case mu::io::token_id::left_square:
        {
            parser.stream.tokens.consume (1);
            auto done (false);
            while (!done && result.error == nullptr)
            {
                auto next (parser.stream.peek ());
                if (next.ast != nullptr)
                {
                    expression_l->arguments.push_back (next.ast);
                    parser.stream.consume ();
                }
                else if (next.token != nullptr)
                {
                    switch (next.token->id ())
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
    auto name (parser_a.stream.peek ());
    if (name.token != nullptr)
    {
        auto name_id (name.token->id ());
        switch (name_id)
        {
            case mu::io::token_id::identifier:
            {
                parser_a.stream.consume ();
                auto next (parser_a.stream.peek ());
                if (next.ast != nullptr)
                {
                    auto error (parser_a.current_mapping->insert(static_cast <mu::io::identifier *> (name.token)->string, next.ast));
                    if (error)
                    {
                        result.error = new (GC) mu::core::error_string (U"Unable to use name");
                    }
                    else
                    {
                        result.node = next.ast;
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
    mu::llvmc::node_result result ({nullptr, nullptr});
    parser_a.stream.consume ();
    auto next (parser_a.stream.peek ());
    if (next.ast != nullptr)
    {
        parser_a.stream.consume ();
        auto expression (new (GC) mu::llvmc::ast::if_expression);
        expression->predicate = next.ast;
        result.error = parse_branch (parser_a, expression->true_roots);
        if (result.error == nullptr)
        {
            parser_a.stream.consume ();
            result.error = parse_branch (parser_a, expression->false_roots);
        }
        if (result.error == nullptr)
        {
            result.node = expression;
        }
    }
    else if (next.token != nullptr)
    {
        result.error = new (GC) mu::core::error_string (U"Expecting expression");
    }
    else
    {
        result.error = next.error;
    }
    return result;
}

mu::core::error * mu::llvmc::if_hook::parse_branch (mu::llvmc::parser & parser_a, mu::vector <mu::llvmc::ast::node *> & target)
{
    mu::core::error * result (nullptr);
    switch (parser_a.stream.tokens [0]->id ())
    {
        case mu::io::token_id::left_square:
        {
            parser_a.stream.tokens.consume (1);
            auto done (false);
            while (!done)
            {
                switch (parser_a.stream.tokens [0]->id ())
                {
                    case mu::io::token_id::right_square:
                        done = true;
                        break;
                    default:
                    {
                        auto next (parser_a.stream.peek ());
                        if (next.ast != nullptr)
                        {
                            target.push_back (next.ast);
                            parser_a.stream.consume ();
                        }
                        else if (next.token != nullptr)
                        {
                            result = new (GC) mu::core::error_string (U"Expecting expression");
                        }
                        else
                        {
                            result = next.error;
                        }
                        
                    }
                        break;
                }
            }
        }
            break;
        default:
            result = new (GC) mu::core::error_string (U"Expecting left square");
            break;
    }
    return result;
}

bool mu::llvmc::if_hook::covering ()
{
    return false;
}

mu::llvmc::loop::loop (mu::llvmc::parser & parser_a):
loop_m (new (GC) mu::llvmc::ast::loop),
result ({nullptr, nullptr}),
parser (parser_a)
{
}

void mu::llvmc::loop::parse ()
{
    parser.stream.consume ();
    parse_arguments ();
    if (result.error == nullptr)
    {
        parse_binds ();
        if (result.error == nullptr)
        {
            parse_body ();
            if (result.error == nullptr)
            {
                parse_results ();
                if (result.error == nullptr)
                {
                    result.node = loop_m;
                }
            }
        }
    }
}

void mu::llvmc::loop::parse_arguments ()
{
    switch (parser.stream.tokens [0]->id ())
    {
        case mu::io::token_id::left_square:
        {
            parser.stream.tokens.consume (1);
            auto done (false);
            while (!done)
            {
                auto next (parser.stream.peek ());
                if (next.ast != nullptr)
                {
                    parser.stream.consume ();
                    loop_m->arguments.push_back (next.ast);
                }
                else if (next.token != nullptr)
                {
                    switch (next.token->id ())
                    {
                        case mu::io::token_id::right_square:
                            parser.stream.consume ();
                            done = true;
                            break;
                        case mu::io::token_id::identifier:
                        {
                            parser.stream.consume ();
                            auto & arguments_l (loop_m->arguments);
                            auto position (arguments_l.size ());
                            arguments_l.push_back (nullptr);
                            parser.current_mapping->refer (static_cast <mu::io::identifier *> (next.token)->string,
                                                          [&arguments_l, position]
                                                           (mu::llvmc::ast::node * node_a)
                                                          {
                                                              arguments_l [position] = node_a;
                                                          });
                        }
                            break;
                        default:
                            done = true;
                            result.error = new (GC) mu::core::error_string (U"Expecting argument or right square");
                            break;
                    }
                }
                else
                {
                    result.error = next.error;
                    done = true;
                }
            }
        }
            break;
        default:
            result.error = new (GC) mu::core::error_string (U"Expecting left square");
            break;
    }
}

void mu::llvmc::loop::parse_binds ()
{
    switch (parser.stream.tokens [0]->id ())
    {
        case mu::io::token_id::left_square:
        {
            parser.stream.tokens.consume (1);
            auto done (false);
            while (!done)
            {
                auto next (parser.stream.peek ());
                if (next.ast != nullptr)
                {
                    done = true;
                    result.error = new (GC) mu::core::error_string (U"Expecting identifier");
                }
                else if (next.token != nullptr)
                {
                    switch (next.token->id ())
                    {
                        case mu::io::token_id::identifier:
                        {
                            auto parameter (new (GC) mu::llvmc::ast::loop_argument);
                            loop_m->parameters.push_back (parameter);
                            auto error (parser.current_mapping->insert(static_cast <mu::io::identifier *> (next.token)->string, parameter));
                            if (!error)
                            {
                                parser.stream.consume ();
                            }
                            else
                            {
                                done = true;
                                result.error = new (GC) mu::core::error_string (U"Unable to use identifier");
                            }
                        }
                            break;
                        case mu::io::token_id::right_square:
                            done = true;
                            parser.stream.consume ();
                            break;
                        default:
                            done = true;
                            result.error = new (GC) mu::core::error_string (U"Expecting identifier");
                            break;
                    }
                }
                else
                {
                    done = true;
                    result.error = next.error;
                }
            }
        }
            break;
        default:
            result.error = new (GC) mu::core::error_string (U"Expecting left square");
            break;
    }
}

void mu::llvmc::loop::parse_body ()
{
    switch (parser.stream.tokens [0]->id ())
    {
        case mu::io::token_id::left_square:
        {
            parser.stream.tokens.consume (1);
            auto done (false);
            while (!done)
            {
                auto next (parser.stream.peek ());
                if (next.ast != nullptr)
                {
                    loop_m->roots.push_back (next.ast);
                    parser.stream.consume ();
                }
                else if (next.token != nullptr)
                {
                    switch (next.token->id ())
                    {
                        case mu::io::token_id::right_square:
                            done = true;
                            parser.stream.consume ();
                            break;
                        default:
                            done = true;
                            result.error = new (GC) mu::core::error_string (U"Expecting expression or right square");
                            break;
                    }
                }
                else
                {
                    result.error = next.error;
                    done = true;
                }
            }
        }
            break;
        default:
            result.error = new (GC) mu::core::error_string (U"Expecting loop body");
            break;
    }
}

void mu::llvmc::loop::parse_results ()
{
    switch (parser.stream.tokens [0]->id ())
    {
        case mu::io::token_id::left_square:
        {
            parser.stream.tokens.consume (1);
            auto done (false);
            while (!done && result.error == nullptr)
            {
                switch (parser.stream.tokens [0]->id ())
                {
                    case mu::io::token_id::left_square:
                    {
                        parser.stream.tokens.consume (1);
                        loop_m->results.push_back (decltype (loop_m->results)::value_type ());
                        auto & set (loop_m->results [loop_m->results.size () - 1]);
                        auto set_done (false);
                        while (!set_done && result.error == nullptr)
                        {
                            auto next (parser.stream.peek ());
                            if (next.ast != nullptr)
                            {
                                result.error = new (GC) mu::core::error_string (U"Expecting result identifiers");
                            }
                            else if (next.token != nullptr)
                            {
                                switch (next.token->id ())
                                {
                                    case mu::io::token_id::identifier:
                                    {
                                        parser.stream.consume ();
                                        auto position (set.size ());
                                        set.push_back (nullptr);
                                        parser.current_mapping->refer (static_cast <mu::io::identifier *> (next.token)->string,
                                                                      [&set, position]
                                                                       (mu::llvmc::ast::node * node_a)
                                                                      {
                                                                          set [position] = node_a;
                                                                      });
                                    }
                                        break;
                                    case mu::io::token_id::right_square:
                                        parser.stream.consume ();
                                        set_done = true;
                                        break;
                                    default:
                                        result.error = new (GC) mu::core::error_string (U"Expecting identifier");
                                        break;
                                }
                            }
                            else
                            {
                                result.error = next.error;
                            }
                        }
                    }
                        break;
                    case mu::io::token_id::right_square:
                        done = true;
                        break;
                    default:
                        result.error = new (GC) mu::core::error_string (U"Expecting result set or right square");
                        break;
                }
            }
        }
            break;
        default:
            result.error = new (GC) mu::core::error_string (U"Expecting loop results");
            break;
    }
}

mu::llvmc::node_result mu::llvmc::loop_hook::parse (mu::string const & data_a, mu::llvmc::parser & parser_a)
{
    assert (data_a.empty ());
    mu::llvmc::loop loop (parser_a);
    loop.parse ();
    return loop.result;
}

bool mu::llvmc::loop_hook::covering ()
{
    return false;
}