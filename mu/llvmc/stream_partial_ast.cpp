#include <mu/llvmc/stream_partial_ast.hpp>

#include <mu/llvmc/parser.hpp>
#include <mu/io/stream_token.hpp>
#include <mu/io/tokens.hpp>

#include <gc_cpp.h>

mu::llvmc::partial_ast::~partial_ast ()
{
    assert ((token != nullptr) xor (ast != nullptr));
}

mu::llvmc::stream_partial_ast::stream_partial_ast (mu::io::stream_token & tokens_a, mu::llvmc::parser & parser_a, size_t size_a):
buffer (size_a),
tokens (tokens_a),
parser (parser_a)
{
    refill ();
}

void mu::llvmc::stream_partial_ast::consume (size_t size_a)
{
    assert (size_a <= size ());
    buffer.erase_begin (size_a);
    refill ();
}

mu::llvmc::partial_ast & mu::llvmc::stream_partial_ast::operator [] (size_t size_a)
{
    assert (size_a <= size ());
    auto & result (buffer [size_a]);
    return result;
}

size_t mu::llvmc::stream_partial_ast::size ()
{
    auto result (buffer.capacity ());
    return result;
}

void mu::llvmc::stream_partial_ast::refill ()
{
    auto needed (size () - buffer.size ());
    auto & tokens_l (tokens);
    for (size_t i (0); i < needed; ++i)
    {
        auto token (tokens_l [0]);
        auto id (token->id ());
        switch (id)
        {
            case mu::io::token_id::identifier:
            {
                auto identifier (static_cast <mu::io::identifier *> (token));
                auto hook (parser.keywords.get_hook (identifier->string));
                if (hook.hook != nullptr)
                {
                    hook.hook->parse (hook.data, parser);
                }
                else
                {
                    buffer.push_back (mu::llvmc::partial_ast ({token, nullptr}));
                }
            }
                break;
            default:
                buffer.push_back (mu::llvmc::partial_ast ({token, nullptr}));
                break;
        }
    }
}