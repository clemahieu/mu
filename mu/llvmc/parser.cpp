#include <mu/llvmc/parser.hpp>

#include <mu/core/error_string.hpp>
#include <mu/io/stream.hpp>
#include <mu/io/tokens.hpp>
#include <mu/llvmc/ast.hpp>
#include <mu/llvmc/partial_ast.hpp>
#include <mu/io/stream_token.hpp>
#include <mu/llvmc/skeleton.hpp>
#include <mu/llvmc/parser_t.hpp>

#include <llvm/Type.h>

#include <gc_cpp.h>

#include <sstream>

mu::llvmc::global::global (mu::llvmc::keywords * keywords_a) :
keywords (keywords_a)
{
}

mu::llvmc::parser::parser (mu::io::stream_token & stream_a):
globals (&keywords),
current_mapping (&globals),
stream (stream_a)
{
    bool error (false);
    error = globals.insert  (U"~", new (GC) mu::llvmc::ast::value (new (GC) mu::llvmc::skeleton::identity));
    assert (!error);
    error = keywords.insert (U"#", &number);
    assert (!error);
    error = keywords.insert (U"asm", &asm_hook);
    assert (!error);
    error = keywords.insert (U"cint", &constant_int);
    assert (!error);
    error = keywords.insert (U"function", &function);
    assert (!error);
    error = keywords.insert (U"int", &int_type);
    assert (!error);
    error = keywords.insert (U"loop", &loop_hook);
    assert (!error);
    error = keywords.insert (U"let", &let_hook);
    assert (!error);
    error = keywords.insert (U"ptr", &ptr_type);
    assert (!error);
    error = keywords.insert (U"set", &set_hook);
    assert (!error);
    error = globals.insert  (U"false", new (GC) mu::llvmc::ast::constant_int (U"1", new (GC) mu::llvmc::ast::number (U"0")));
    assert (!error);
    error = globals.insert  (U"true", new (GC) mu::llvmc::ast::constant_int (U"1", new (GC) mu::llvmc::ast::number (U"1")));
    assert (!error);
    error = globals.insert (U"unit_v", new (GC) mu::llvmc::ast::unit);
    assert (!error);
    error = globals.insert (U"join", new (GC) mu::llvmc::ast::value (new (GC) mu::llvmc::skeleton::join));
    assert (!error);
    error = globals.insert (U"add", new (GC) mu::llvmc::ast::value (new (GC) mu::llvmc::skeleton::marker (mu::llvmc::instruction_type::add)));
    assert (!error);
    error = globals.insert (U"alloca", new (GC) mu::llvmc::ast::value (new (GC) mu::llvmc::skeleton::marker (mu::llvmc::instruction_type::alloca)));
    assert (!error);
    error = globals.insert (U"and", new (GC) mu::llvmc::ast::value (new (GC) mu::llvmc::skeleton::marker (mu::llvmc::instruction_type::and_i)));
    assert (!error);
    error = globals.insert (U"ashr", new (GC) mu::llvmc::ast::value (new (GC) mu::llvmc::skeleton::marker (mu::llvmc::instruction_type::ashr)));
    assert (!error);
    error = globals.insert (U"atomicrmw", new (GC) mu::llvmc::ast::value (new (GC) mu::llvmc::skeleton::marker (mu::llvmc::instruction_type::atomicrmw)));
    assert (!error);
    error = globals.insert (U"bitcast", new (GC) mu::llvmc::ast::value (new (GC) mu::llvmc::skeleton::marker (mu::llvmc::instruction_type::bitcast)));
    assert (!error);
    error = globals.insert (U"call", new (GC) mu::llvmc::ast::value (new (GC) mu::llvmc::skeleton::marker (mu::llvmc::instruction_type::call)));
    assert (!error);
    error = globals.insert (U"cmpxchg", new (GC) mu::llvmc::ast::value (new (GC) mu::llvmc::skeleton::marker (mu::llvmc::instruction_type::cmpxchg)));
    assert (!error);
    error = globals.insert (U"eq", new (GC) mu::llvmc::ast::value (new (GC) mu::llvmc::skeleton::predicate (mu::llvmc::predicates::icmp_eq)));
    assert (!error);
    error = globals.insert (U"extractelement", new (GC) mu::llvmc::ast::value (new (GC) mu::llvmc::skeleton::marker (mu::llvmc::instruction_type::extractelement)));
    assert (!error);
    error = globals.insert (U"extractvalue", new (GC) mu::llvmc::ast::value (new (GC) mu::llvmc::skeleton::marker (mu::llvmc::instruction_type::extractvalue)));
    assert (!error);
    error = globals.insert (U"fadd", new (GC) mu::llvmc::ast::value (new (GC) mu::llvmc::skeleton::marker (mu::llvmc::instruction_type::fadd)));
    assert (!error);
    error = globals.insert (U"fcmp", new (GC) mu::llvmc::ast::value (new (GC) mu::llvmc::skeleton::marker (mu::llvmc::instruction_type::fcmp)));
    assert (!error);
    error = globals.insert (U"fdiv", new (GC) mu::llvmc::ast::value (new (GC) mu::llvmc::skeleton::marker (mu::llvmc::instruction_type::fdiv)));
    assert (!error);
    error = globals.insert (U"fence", new (GC) mu::llvmc::ast::value (new (GC) mu::llvmc::skeleton::marker (mu::llvmc::instruction_type::fence)));
    assert (!error);
    error = globals.insert (U"fmul", new (GC) mu::llvmc::ast::value (new (GC) mu::llvmc::skeleton::marker (mu::llvmc::instruction_type::fmul)));
    assert (!error);
    error = globals.insert (U"fpext", new (GC) mu::llvmc::ast::value (new (GC) mu::llvmc::skeleton::marker (mu::llvmc::instruction_type::fpext)));
    assert (!error);
    error = globals.insert (U"fptoi", new (GC) mu::llvmc::ast::value (new (GC) mu::llvmc::skeleton::marker (mu::llvmc::instruction_type::fptoi)));
    assert (!error);
    error = globals.insert (U"fptosi", new (GC) mu::llvmc::ast::value (new (GC) mu::llvmc::skeleton::marker (mu::llvmc::instruction_type::fptosi)));
    assert (!error);
    error = globals.insert (U"fptoui", new (GC) mu::llvmc::ast::value (new (GC) mu::llvmc::skeleton::marker (mu::llvmc::instruction_type::fptoui)));
    assert (!error);
    error = globals.insert (U"fptrunc", new (GC) mu::llvmc::ast::value (new (GC) mu::llvmc::skeleton::marker (mu::llvmc::instruction_type::fptrunc)));
    assert (!error);
    error = globals.insert (U"frem", new (GC) mu::llvmc::ast::value (new (GC) mu::llvmc::skeleton::marker (mu::llvmc::instruction_type::frem)));
    assert (!error);
    error = globals.insert (U"fsub", new (GC) mu::llvmc::ast::value (new (GC) mu::llvmc::skeleton::marker (mu::llvmc::instruction_type::fsub)));
    assert (!error);
    error = globals.insert (U"getelementptr", new (GC) mu::llvmc::ast::value (new (GC) mu::llvmc::skeleton::marker (mu::llvmc::instruction_type::getelementptr)));
    assert (!error);
    error = globals.insert (U"icmp", new (GC) mu::llvmc::ast::value (new (GC) mu::llvmc::skeleton::marker (mu::llvmc::instruction_type::icmp)));
    assert (!error);
    error = globals.insert (U"if", new (GC) mu::llvmc::ast::value (new (GC) mu::llvmc::skeleton::marker (mu::llvmc::instruction_type::if_i)));
    assert (!error);
    error = globals.insert (U"insertelement", new (GC) mu::llvmc::ast::value (new (GC) mu::llvmc::skeleton::marker (mu::llvmc::instruction_type::insertelement)));
    assert (!error);
    error = globals.insert (U"insertvalue", new (GC) mu::llvmc::ast::value (new (GC) mu::llvmc::skeleton::marker (mu::llvmc::instruction_type::insertvalue)));
    assert (!error);
    error = globals.insert (U"load", new (GC) mu::llvmc::ast::value (new (GC) mu::llvmc::skeleton::marker (mu::llvmc::instruction_type::load)));
    assert (!error);
    error = globals.insert (U"lshr", new (GC) mu::llvmc::ast::value (new (GC) mu::llvmc::skeleton::marker (mu::llvmc::instruction_type::lshr)));
    assert (!error);
    error = globals.insert (U"mul", new (GC) mu::llvmc::ast::value (new (GC) mu::llvmc::skeleton::marker (mu::llvmc::instruction_type::mul)));
    assert (!error);
    error = globals.insert (U"or", new (GC) mu::llvmc::ast::value (new (GC) mu::llvmc::skeleton::marker (mu::llvmc::instruction_type::or_i)));
    assert (!error);
    error = globals.insert (U"ptrfromint", new (GC) mu::llvmc::ast::value (new (GC) mu::llvmc::skeleton::marker (mu::llvmc::instruction_type::inttoptr)));
    assert (!error);
    error = globals.insert (U"ptrtoint", new (GC) mu::llvmc::ast::value (new (GC) mu::llvmc::skeleton::marker (mu::llvmc::instruction_type::ptrtoint)));
    assert (!error);
    error = globals.insert (U"sdiv", new (GC) mu::llvmc::ast::value (new (GC) mu::llvmc::skeleton::marker (mu::llvmc::instruction_type::sdiv)));
    assert (!error);
    error = globals.insert (U"select", new (GC) mu::llvmc::ast::value (new (GC) mu::llvmc::skeleton::marker (mu::llvmc::instruction_type::select)));
    assert (!error);
    error = globals.insert (U"sext", new (GC) mu::llvmc::ast::value (new (GC) mu::llvmc::skeleton::marker (mu::llvmc::instruction_type::sext)));
    assert (!error);
    error = globals.insert (U"shl", new (GC) mu::llvmc::ast::value (new (GC) mu::llvmc::skeleton::marker (mu::llvmc::instruction_type::shl)));
    assert (!error);
    error = globals.insert (U"shufflevector", new (GC) mu::llvmc::ast::value (new (GC) mu::llvmc::skeleton::marker (mu::llvmc::instruction_type::shufflevector)));
    assert (!error);
    error = globals.insert (U"sitofp", new (GC) mu::llvmc::ast::value (new (GC) mu::llvmc::skeleton::marker (mu::llvmc::instruction_type::sitofp)));
    assert (!error);
    error = globals.insert (U"srem", new (GC) mu::llvmc::ast::value (new (GC) mu::llvmc::skeleton::marker (mu::llvmc::instruction_type::srem)));
    assert (!error);
    error = globals.insert (U"store", new (GC) mu::llvmc::ast::value (new (GC) mu::llvmc::skeleton::marker (mu::llvmc::instruction_type::store)));
    assert (!error);
    error = globals.insert (U"sub", new (GC) mu::llvmc::ast::value (new (GC) mu::llvmc::skeleton::marker (mu::llvmc::instruction_type::sub)));
    assert (!error);
    error = globals.insert (U"switch", new (GC) mu::llvmc::ast::value (new (GC) mu::llvmc::skeleton::marker (mu::llvmc::instruction_type::switch_i)));
    assert (!error);
    error = globals.insert (U"trunc", new (GC) mu::llvmc::ast::value (new (GC) mu::llvmc::skeleton::marker (mu::llvmc::instruction_type::trunc)));
    assert (!error);
    error = globals.insert (U"udiv", new (GC) mu::llvmc::ast::value (new (GC) mu::llvmc::skeleton::marker (mu::llvmc::instruction_type::udiv)));
    assert (!error);
    error = globals.insert (U"uitofp", new (GC) mu::llvmc::ast::value (new (GC) mu::llvmc::skeleton::marker (mu::llvmc::instruction_type::uitofp)));
    assert (!error);
    error = globals.insert (U"urem", new (GC) mu::llvmc::ast::value (new (GC) mu::llvmc::skeleton::marker (mu::llvmc::instruction_type::urem)));
    assert (!error);
    error = globals.insert (U"void", new (GC) mu::llvmc::ast::value (new (GC) mu::llvmc::skeleton::void_t));
    assert (!error);
    error = globals.insert (U"xor", new (GC) mu::llvmc::ast::value (new (GC) mu::llvmc::skeleton::marker (mu::llvmc::instruction_type::xor_i)));
    assert (!error);
    error = globals.insert (U"zext", new (GC) mu::llvmc::ast::value (new (GC) mu::llvmc::skeleton::marker (mu::llvmc::instruction_type::zext)));
    assert (!error);
}

mu::llvmc::node_result mu::llvmc::module::parse (mu::string const & data_a, mu::llvmc::parser & parser_a)
{
    mu::llvmc::node_result result ({nullptr, nullptr});
    auto module (new (GC) mu::llvmc::ast::module);
	module->region.first = mu::core::position (0, 1, 1);
    while ((result.node == nullptr) and (result.error == nullptr))
    {
        auto item (parser_a.peek ());
        if (item.ast != nullptr)
        {
            module->functions.push_back (item.ast);
            parser_a.consume ();
        }
        else if (item.token != nullptr)
        {
            auto id (item.token->id ());
            switch (id)
            {
                case mu::io::token_id::end:
					module->region.last = item.token->region.last;
                    result.node = module;
                    break;
                default:                    
                    result.error = new (GC) mu::core::error_string (U"Expecting function or end of stream", mu::core::error_type::expecting_function_or_end_of_stream);
                    break;
            }
        }
        else
        {
            result.error = item.error;
        }
    }
    if (result.error == nullptr)
    {
        if (!parser_a.globals.unresolved.empty ())
        {
			std::stringstream error;
			error << "Unresoled symbols:";
			for (auto i: parser_a.globals.unresolved)
			{
				error << " " << std::string (i.first.begin (), i.first.end ());
			}
			std::string err (error.str ());
            result.error = new (GC) mu::core::error_string (mu::string (err.begin (), err.end ()).c_str (), mu::core::error_type::unresolved_symbols);
            result.node = nullptr;
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
	function_m->region.first = parser.stream [0]->region.first;
    parser.consume ();
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
					function_m->region.last = parser.stream [0]->region.last;
                    result.node = function_m;
                }
            }
        }
    }
}

void mu::llvmc::function::parse_name ()
{
    result.error = parser.parse_identifier (
        [&]
        (mu::io::identifier * identifier_a)
        {
			mu::core::error * result (nullptr);
            auto name (static_cast <mu::io::identifier *> (parser.peek ().token));
            function_m->name = name->string;
            auto error (parser.globals.insert (name->string, function_m));
            if (error)
            {
                result = new (GC) mu::core::error_string (U"Function name already used", mu::core::error_type::function_name_already_used);
            }
			return result;
        }, U"Expecting identifier", mu::core::error_type::expecting_identifier);
    if (result.error == nullptr)
    {
        parser.consume ();
    }
}

void mu::llvmc::function::parse_parameters ()
{
    switch (parser.stream [0]->id ())
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
            result.error = new (GC) mu::core::error_string (U"While parsing parameters, expecting left square", mu::core::error_type::parsing_parameters_expecting_left_square);
            break;
    }
}

void mu::llvmc::function::parse_parameter (bool & done_a)
{
    auto argument (new (GC) mu::llvmc::ast::parameter);
	result.error = parser.parse_ast_or_refer_or_right_square (
		[&]
		(mu::llvmc::ast::node * node_a)
		{
			argument->type = node_a;
		},
		[&]
		(mu::io::right_square * right_square_a)
		{
			done_a = true;
		},
		U"Expecting type or right square", mu::core::error_type::expecting_type_or_right_square);
	if (result.error == nullptr && !done_a)
	{
		function_m->parameters.push_back (argument);
        result.error = parser.parse_identifier (
            [&]
            (mu::io::identifier * identifier_a)
            {
				mu::core::error * result (nullptr);
				argument->name = identifier_a->string;
                if (block.insert (identifier_a->string, argument))
                {
                    result = new (GC) mu::core::error_string (U"Unable to use identifier", mu::core::error_type::unable_to_use_identifier);
                }
				return result;
            }, U"While parsing parameters, expecting an identifier", mu::core::error_type::parsing_parameters_expecting_identifier);	
		parser.consume ();
	}
}

void mu::llvmc::function::parse_body ()
{
    switch (parser.stream [0]->id ())
    {
        case mu::io::token_id::left_square:
        {
            parser.stream.consume (1);
            auto done (false);
            while (!done && result.error == nullptr)
            {
                switch (parser.stream [0]->id ())
                {
                    case mu::io::token_id::right_square:
                        parser.stream.consume (1);
                        done = true;
                        break;
                    default:
                    {
                        auto next (parser.peek ());
                        if (next.ast != nullptr)
                        {
                            parser.consume ();
                            function_m->roots.push_back (next.ast);
                        }
                        else if (next.token != nullptr)
                        {
                            result.error = new (GC) mu::core::error_string (U"Expecting expression", mu::core::error_type::expecting_expression);
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
            result.error = new (GC) mu::core::error_string (U"Expecting left square", mu::core::error_type::expecting_left_square);
            break;
    }
}

void mu::llvmc::function::parse_results ()
{
    switch (parser.stream [0]->id ())
    {
        case mu::io::token_id::left_square:
        {
            parser.stream.consume (1);
            auto next (parser.stream [0]);
            auto done (false);
            while (result.error == nullptr && !done)
            {
                switch (next->id ())
                {
                    case mu::io::token_id::left_square:
                        parser.stream.consume (1);
                        parse_result_set ();
                        function_m->branch_ends.push_back (function_m->results.size ());
                        next = parser.stream [0];
                        break;
                    case mu::io::token_id::right_square:
                        done = true;
                        break;
                    default:
                        result.error = new (GC) mu::core::error_string (U"Expecting identifier or right square", mu::core::error_type::expecting_identifier_or_right_square);
                        break;
                }
            }
        }
            break;
        default:
            result.error = new (GC) mu::core::error_string (U"Expecting left square", mu::core::error_type::expecting_left_square);
            break;
    }
}

void mu::llvmc::function::parse_result_set ()
{
	auto first (parser.stream [0]->region);
    auto node (parser.peek ());
    auto done (false);
    auto predicates (false);
    while (result.error == nullptr && !done)
    {
        if (node.ast != nullptr)
        {
            if (!predicates)
            {
                auto type (node.ast);
                parser.consume ();
                result.error = parser.parse_ast_or_refer (
                    [&]
                    (mu::llvmc::ast::node * node_a)
                    {
                        auto result (new (GC) mu::llvmc::ast::result (type));
                        result->region = mu::core::region (first.first, parser.stream [0]->region.last);
                        function_m->results.push_back (result);
                        result->value = node_a;
                    });
                if (result.error == nullptr)
                {
                    parser.consume ();
                    node = parser.peek ();
                }
            }
            else
            {
                function_m->results.push_back (node.ast);
                parser.consume ();
                node = parser.peek ();
            }
        }
        else if (node.token != nullptr)
        {
            auto node_id (node.token->id ());
            switch (node_id)
            {
                case mu::io::token_id::right_square:
                    parser.consume ();
                    done = true;
                    if (!predicates)
                    {
                        function_m->predicate_offsets.push_back (function_m->results.size ());
                    }
                    break;
                case mu::io::token_id::terminator:
                {
                    parser.consume ();
                    node = parser.peek ();
                    if (predicates == false)
                    {
                        predicates = true;
                        function_m->predicate_offsets.push_back (function_m->results.size ());
                    }
                    else
                    {
                        result.error = new (GC) mu::core::error_string (U"Already parsing predicates", mu::core::error_type::already_parsing_predicates);
                    }
                    break;
                }
                case mu::io::token_id::identifier:
                {
                    if (predicates)
                    {
                        auto index (function_m->results.size ());
                        function_m->results.push_back (nullptr);
                        auto function_l (function_m);
                        block.refer (static_cast <mu::io::identifier *> (node.token)->string,
                                     [function_l, index]
                                     (mu::llvmc::ast::node * node_a)
                                     {
                                         function_l->results [index] = node_a;
                                     });
                        parser.consume ();
                        node = parser.peek ();
                    }
                    else
                    {
                        result.error = new (GC) mu::core::error_string (U"Expecting result reference", mu::core::error_type::expecting_result_reference);
                    }
                    break;
                }
                default:
                    result.error = new (GC) mu::core::error_string (U"Expecting right_square", mu::core::error_type::expecting_right_square);
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

bool mu::llvmc::global::get (mu::string const & name_a, action_type action_a)
{
    auto existing (mappings.find (name_a));
    auto result (existing == mappings.end ());
    if (!result)
    {
        action_a (existing->second);
    }
    return result;
}

void mu::llvmc::global::refer (mu::string const & name_a, action_type action_a)
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

bool mu::llvmc::block::get (mu::string const & name_a, action_type action_a)
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

void mu::llvmc::block::refer (mu::string const & name_a, action_type action_a)
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

void mu::llvmc::block::accept (mu::multimap <mu::string, action_type> unresolved_a)
{
    unresolved.insert (unresolved_a.begin (), unresolved_a.end ());
}

void mu::llvmc::global::accept (mu::multimap <mu::string, action_type> unresolved_a)
{
    unresolved.insert (unresolved_a.begin (), unresolved_a.end ());
}

mu::llvmc::node_result mu::llvmc::int_type::parse (mu::string const & data_a, mu::llvmc::parser & parser_a)
{
    mu::llvmc::node_result result ({nullptr, nullptr});
    result.node = new (GC) mu::llvmc::ast::integer_type (data_a);
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
    switch (parser.stream [0]->id ())
    {
        case mu::io::token_id::left_square:
        {
            expression_l->region.first = parser.stream [0]->region.first;
            parser.stream.consume (1);
            auto done (false);
            auto predicates (false);
            while (!done && result.error == nullptr)
            {
                auto next (parser.peek ());
                if (next.ast != nullptr)
                {
                    expression_l->arguments.push_back (next.ast);
                    parser.consume ();
                }
                else if (next.token != nullptr)
                {
                    switch (next.token->id ())
                    {
                        case mu::io::token_id::identifier:
                        {
                            parser.consume ();
                            auto & arguments (expression_l->arguments);
                            auto position (expression_l->arguments.size ());
                            expression_l->arguments.push_back (nullptr);
                            parser.current_mapping->refer(static_cast <mu::io::identifier *> (next.token)->string,
                                [&arguments, position]
                                (mu::llvmc::ast::node * node_a)
                                {
                                    arguments [position] = node_a;
                                });
                            break;
                        }
                        case mu::io::token_id::terminator:
                        {
                            predicates = true;
                            auto position_l (expression_l->predicate_position);
                            if (position_l == (0 - 1))
                            {
                                expression_l->set_predicate_position ();
                            }
                            else
                            {
                                result.error = new (GC) mu::core::error_string (U"Already parsing predicates", mu::core::error_type::already_parsing_predicates);
                            }
                            parser.consume ();
                            break;
                        }
                        case mu::io::token_id::right_square:
                            expression_l->region.last = parser.stream [0]->region.first;
                            done = true;
                            break;
                        default:
                            result.error = new (GC) mu::core::error_string (U"Expecting argument or right_square", mu::core::error_type::expecting_argument_or_right_square);
                            break;
                    }
                }
                else
                {
                    result.error = next.error;
                }
            }
            if (!predicates)
            {
                expression_l->set_predicate_position ();
            }
        }
            break;
        default:
            result.error = new (GC) mu::core::error_string (U"Expecting left square", mu::core::error_type::expecting_left_square);
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
    parser_a.consume ();
    auto name (parser_a.peek ());
    if (name.token != nullptr)
    {
        auto name_id (name.token->id ());
        switch (name_id)
        {
            case mu::io::token_id::identifier:
            {
                parser_a.consume ();
                auto next (parser_a.peek ());
                if (next.ast != nullptr)
                {
                    auto error (parser_a.current_mapping->insert(static_cast <mu::io::identifier *> (name.token)->string, next.ast));
                    if (error)
                    {
                        result.error = new (GC) mu::core::error_string (U"Unable to use name", mu::core::error_type::unable_to_use_identifier);
                    }
                    else
                    {
                        result.node = next.ast;
                    }
                }
                else if (next.ast != nullptr)
                {
                    result.error = new (GC) mu::core::error_string (U"Expecting an expression", mu::core::error_type::expecting_expression);
                }
                else
                {
                    result.error = next.error;
                }
            }
                break;
            default:
                result.error = new (GC) mu::core::error_string (U"Expecting identifier", mu::core::error_type::expecting_identifier);
                break;
        }
    }
    else if (name.ast != nullptr)
    {
        result.error = new (GC) mu::core::error_string (U"Expecting a name", mu::core::error_type::expecting_name);
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

mu::llvmc::node_result mu::llvmc::let_hook::parse (mu::string const & data_a, mu::llvmc::parser & parser_a)
{
    assert (data_a.empty ());
    mu::llvmc::node_result result ({nullptr, nullptr});
    parser_a.consume ();
    auto done (false);
    auto next (parser_a.stream [0]);
    mu::vector <mu::io::identifier *> identifiers;
    while (!done && result.error == nullptr)
    {
        switch (next->id ())
        {
            case mu::io::token_id::identifier:
            {
                auto identifier (static_cast <mu::io::identifier *> (next));
                auto hook (parser_a.keywords.get_hook (identifier->string));
                if (hook.hook != nullptr)
                {
                    done = true;
                }
                else
                {
                    identifiers.push_back (identifier);
                    parser_a.stream.consume (1);
                    next = parser_a.stream [0];
                }
                break;
            }
            case mu::io::token_id::left_square:
                done = true;
                break;
            default:
                result.error = new (GC) mu::core::error_string (U"Expecting identifier or left square", mu::core::error_type::expecting_identifier_or_left_square);
                break;
        }
    }
    auto set (new (GC) mu::llvmc::ast::set_expression);
	auto expression (parser_a.peek ());
	if (expression.ast != nullptr)
	{
		set->items.push_back (expression.ast);
		result.node = set;
		size_t index (0);
		size_t total (identifiers.size ());
		for (auto i (identifiers.begin ()), j (identifiers.end ()); i != j; ++i, ++index)
		{
			parser_a.current_mapping->insert ((*i)->string, new (GC) mu::llvmc::ast::element (set, index, total, (*i)->string, (*i)->region));
		}
	}
	else
	{
		assert (expression.token == nullptr);
		result.error = expression.error;
	}
    return result;
}

bool mu::llvmc::let_hook::covering ()
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
            for (auto i (unresolved.find (identifier_a)), j (unresolved.end ()); i != j && i->first == identifier_a; ++i)
            {
                i->second (node_a);
            }
            unresolved.erase (identifier_a);
        }
    }
    return result;
}

mu::llvmc::loop::loop (mu::llvmc::parser & parser_a):
loop_m (new (GC) mu::llvmc::ast::loop),
result ({nullptr, nullptr}),
parser (parser_a)
{
}

void mu::llvmc::loop::parse ()
{
    parser.consume ();
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
    switch (parser.stream [0]->id ())
    {
        case mu::io::token_id::left_square:
        {
            parser.stream.consume (1);
            auto predicates (false);
            auto done (false);
            while (!done)
            {
                auto next (parser.peek ());
                if (next.ast != nullptr)
                {
                    parser.consume ();
                    loop_m->arguments.push_back (next.ast);
                }
                else if (next.token != nullptr)
                {
                    switch (next.token->id ())
                    {
                        case mu::io::token_id::right_square:
                        {
                            parser.consume ();
                            if (!predicates)
                            {
                                loop_m->set_argument_offset ();
                            }
                            done = true;
                            break;
                        }
                        case mu::io::token_id::identifier:
                        {
                            parser.consume ();
                            auto & arguments_l (loop_m->arguments);
                            auto position (arguments_l.size ());
                            arguments_l.push_back (nullptr);
                            parser.current_mapping->refer (static_cast <mu::io::identifier *> (next.token)->string,
                                  [&arguments_l, position]
                                   (mu::llvmc::ast::node * node_a)
                                  {
                                      arguments_l [position] = node_a;
                                  });
                            break;
                        }
                        case mu::io::token_id::terminator:
                        {
                            parser.consume ();
                            if (!predicates)
                            {
                                predicates = true;
                                loop_m->set_argument_offset ();
                            }
                            else
                            {
                                done = true;
                                result.error = new (GC) mu::core::error_string (U"Already parsing predicates", mu::core::error_type::already_parsing_predicates);
                            }
                            break;
                        }
                        default:
                            done = true;
                            result.error = new (GC) mu::core::error_string (U"Expecting argument or right square", mu::core::error_type::expecting_argument_or_right_square);
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
            result.error = new (GC) mu::core::error_string (U"Expecting left square", mu::core::error_type::expecting_left_square);
            break;
    }
}

void mu::llvmc::loop::parse_binds ()
{
    switch (parser.stream [0]->id ())
    {
        case mu::io::token_id::left_square:
        {
            parser.stream.consume (1);
            auto done (false);
            while (!done)
            {
                auto next (parser.peek ());
                if (next.ast != nullptr)
                {
                    done = true;
                    result.error = new (GC) mu::core::error_string (U"Expecting identifier", mu::core::error_type::expecting_identifier);
                }
                else if (next.token != nullptr)
                {
                    switch (next.token->id ())
                    {
                        case mu::io::token_id::identifier:
                        {
                            auto parameter (new (GC) mu::llvmc::ast::loop_parameter);
                            loop_m->parameters.push_back (parameter);
                            auto error (parser.current_mapping->insert(static_cast <mu::io::identifier *> (next.token)->string, parameter));
                            if (!error)
                            {
                                parser.consume ();
                            }
                            else
                            {
                                done = true;
                                result.error = new (GC) mu::core::error_string (U"Unable to use identifier", mu::core::error_type::unable_to_use_identifier);
                            }
                        }
                            break;
                        case mu::io::token_id::right_square:
                            done = true;
                            parser.consume ();
                            break;
                        default:
                            done = true;
                            result.error = new (GC) mu::core::error_string (U"Expecting identifier", mu::core::error_type::expecting_identifier);
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
            result.error = new (GC) mu::core::error_string (U"Expecting left square", mu::core::error_type::expecting_left_square);
            break;
    }
}

void mu::llvmc::loop::parse_body ()
{
    switch (parser.stream [0]->id ())
    {
        case mu::io::token_id::left_square:
        {
            parser.stream.consume (1);
            auto done (false);
            while (!done)
            {
                auto next (parser.peek ());
                if (next.ast != nullptr)
                {
                    loop_m->roots.push_back (next.ast);
                    parser.consume ();
                }
                else if (next.token != nullptr)
                {
                    switch (next.token->id ())
                    {
                        case mu::io::token_id::right_square:
                            done = true;
                            parser.consume ();
                            break;
                        default:
                            done = true;
                            result.error = new (GC) mu::core::error_string (U"Expecting expression or right square", mu::core::error_type::expecting_expression_or_right_square);
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
            result.error = new (GC) mu::core::error_string (U"Expecting loop body", mu::core::error_type::expecting_loop_body);
            break;
    }
}

void mu::llvmc::loop::parse_results ()
{
    switch (parser.stream [0]->id ())
    {
        case mu::io::token_id::left_square:
        {
            parser.stream.consume (1);
            auto done (false);
            while (!done && result.error == nullptr)
            {
                switch (parser.stream [0]->id ())
                {
                    case mu::io::token_id::left_square:
                    {
                        parser.stream.consume (1);
                        auto set_done (false);
                        auto predicates (false);
                        while (!set_done && result.error == nullptr)
                        {
                            auto next (parser.peek ());
                            if (next.ast != nullptr)
                            {
                                result.error = new (GC) mu::core::error_string (U"Expecting result identifiers", mu::core::error_type::expecting_identifier, next.ast->region);
                            }
                            else if (next.token != nullptr)
                            {
                                switch (next.token->id ())
                                {
                                    case mu::io::token_id::identifier:
                                    {
                                        parser.consume ();
                                        auto position (loop_m->results.size ());
                                        loop_m->results.push_back (nullptr);
                                        parser.current_mapping->refer (static_cast <mu::io::identifier *> (next.token)->string,
                                                                      [&]
                                                                       (mu::llvmc::ast::node * node_a)
                                                                      {
                                                                          loop_m->results [position] = node_a;
                                                                      });
                                        break;
                                    }
                                    case mu::io::token_id::terminator:
                                    {
                                        parser.consume ();
                                        if (!predicates)
                                        {
                                            predicates = true;
                                            loop_m->add_predicate_offset ();
                                        }
                                        else
                                        {
                                            result.error = new (GC) mu::core::error_string (U"Already parsing predicates", mu::core::error_type::already_parsing_predicates);
                                        }
                                        break;
                                    }
                                    case mu::io::token_id::right_square:
                                    {
                                        if (!predicates)
                                        {
                                            loop_m->add_predicate_offset ();
                                        }
                                        loop_m->add_branch_end ();
                                        parser.consume ();
                                        set_done = true;
                                        break;
                                    }
                                    default:
                                        result.error = new (GC) mu::core::error_string (U"Expecting identifier", mu::core::error_type::expecting_identifier);
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
                        result.error = new (GC) mu::core::error_string (U"Expecting result set or right square", mu::core::error_type::expecting_result_set_or_right_square);
                        break;
                }
            }
        }
            break;
        default:
            result.error = new (GC) mu::core::error_string (U"Expecting loop results", mu::core::error_type::expecting_loop_results);
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

mu::llvmc::block::~block ()
{
    parent->accept (unresolved);
}

mu::llvmc::node_result mu::llvmc::ptr_type::parse (mu::string const & data_a, mu::llvmc::parser & parser_a)
{
    assert (data_a == U"");
    mu::llvmc::node_result result ({nullptr, nullptr});
    parser_a.consume ();
    auto item (parser_a.peek ());
    if (item.ast != nullptr)
    {
        result.node = new (GC) mu::llvmc::ast::pointer_type (item.ast);
    }
    else
    {
        result.error = new (GC) mu::core::error_string (U"Expecting a type", mu::core::error_type::expecting_a_type);
    }
    return result;
}

bool mu::llvmc::ptr_type::covering ()
{
    return false;
}

mu::llvmc::node_result mu::llvmc::number::parse (mu::string const & data_a, mu::llvmc::parser & parser_a)
{
    mu::llvmc::node_result result ({nullptr, nullptr});
    result.node = new (GC) mu::llvmc::ast::number (data_a);
    return result;
}

bool mu::llvmc::number::covering ()
{
    return true;
}

mu::llvmc::ast::number::number (mu::string const & number_a) :
number_m (number_a)
{
}

mu::llvmc::node_result mu::llvmc::constant_int::parse (mu::string const & data_a, mu::llvmc::parser & parser_a)
{
    mu::llvmc::node_result result ({nullptr, nullptr});
    parser_a.consume ();
    auto item (parser_a.peek ());
    if (item.ast != nullptr)
    {
        result.node = new (GC) mu::llvmc::ast::constant_int (data_a, item.ast);
    }
    else
    {
        result.error = new (GC) mu::core::error_string (U"Expecting a number", mu::core::error_type::expecting_a_number);
    }
    return result;
}

bool mu::llvmc::constant_int::covering ()
{
    return true;
}

mu::llvmc::node_result mu::llvmc::asm_hook::parse (mu::string const & data_a, mu::llvmc::parser & parser_a)
{
    assert (data_a.empty ());
    mu::llvmc::node_result result ({nullptr, nullptr});
    parser_a.consume ();
    auto asm_l (new (GC) mu::llvmc::ast::asm_c);
    result.error = parser_a.parse_ast_or_refer (
       [&]
       (mu::llvmc::ast::node * node_a)
       {
           asm_l->type = node_a;
       }
    );
    if (result.error == nullptr)
    {
        parser_a.consume ();
        result.error = parser_a.parse_identifier (
        [&]
           (mu::io::identifier * identifier_a)
            {
                asm_l->text = identifier_a->string;
				return nullptr;
            },
        U"Expecting asm text", mu::core::error_type::asm_hook_expecting_identifier);
        if (result.error == nullptr)
        {
            parser_a.consume ();
            result.error = parser_a.parse_identifier (
                [&]
                (mu::io::identifier * identifier_a)
                {
                    asm_l->constraints = identifier_a->string;
					return nullptr;
                },
        U"Expecting asm constraints", mu::core::error_type::asm_hook_expecting_constraints);
            if (result.error == nullptr)
            {
                result.node = asm_l;
            }
        }
    }
    return result;
}

bool mu::llvmc::asm_hook::covering ()
{
    return false;
}

mu::llvmc::partial_ast_result::partial_ast_result (mu::io::token * token_a, mu::llvmc::ast::node * ast_a, mu::core::error * error_a):
token (token_a),
ast (ast_a),
error (error_a)
{
    assert (valid ());
}

mu::llvmc::partial_ast_result::partial_ast_result (mu::llvmc::partial_ast_result const & other_a):
token (other_a.token),
ast (other_a.ast),
error (other_a.error)
{
    assert (valid ());
}

mu::llvmc::partial_ast_result & mu::llvmc::partial_ast_result::operator = (mu::llvmc::partial_ast_result const & other_a)
{
    token = other_a.token;
    ast = other_a.ast;
    error = other_a.error;
    assert (valid ());
    return *this;
}

bool mu::llvmc::partial_ast_result::valid ()
{
    auto result (not ((token != nullptr and ast != nullptr) or (token != nullptr and error != nullptr) or (ast != nullptr and error != nullptr)));
    return result;
}

void mu::llvmc::parser::consume ()
{
    stream.consume (1);
}

mu::llvmc::partial_ast_result mu::llvmc::parser::peek ()
{
    mu::llvmc::partial_ast_result result ({nullptr, nullptr, nullptr});
    auto token (stream [0]);
    auto id (token->id ());
    switch (id)
    {
        case mu::io::token_id::identifier:
        {
            auto identifier (static_cast <mu::io::identifier *> (token));
            auto hook (keywords.get_hook (identifier->string));
            if (hook.hook != nullptr)
            {
                auto ast (hook.hook->parse (hook.data, *this));
                if (ast.node != nullptr)
                {
                    result = {nullptr, ast.node, nullptr};
                }
                else
                {
                    result = {nullptr, nullptr, ast.error};
                }
            }
            else
            {
                result = {token, nullptr, nullptr};
            }
        }
            break;
        case mu::io::token_id::left_square:
        {
            mu::llvmc::expression expression_l (*this);
            expression_l.parse ();
            if (expression_l.result.node != nullptr)
            {
                result.ast = expression_l.result.node;
            }
            else
            {
                result.error = expression_l.result.error;
            }
        }
            break;
        default:
            result = {token, nullptr, nullptr};
            break;
    }
    return result;
}