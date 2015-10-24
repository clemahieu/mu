#include <mu/io/stream_token.hpp>

#include <mu/io/tokens.hpp>
#include <mu/io/lexer.hpp>

mu::io::stream_token::stream_token (mu::io::lexer & lexer_a, size_t size_a):
buffer (size_a),
lexer (lexer_a)
{
    refill ();
}

void mu::io::stream_token::consume (size_t size_a)
{
    assert (size_a <= size ());
    buffer.erase_begin (size_a);
    refill ();
}

mu::io::token * & mu::io::stream_token::operator [] (size_t size_a)
{
    assert (size_a <= size ());
    auto & result (buffer [size_a]);
    return result;
}

size_t mu::io::stream_token::size ()
{
    auto result (buffer.capacity ());
    return result;
}

void mu::io::stream_token::refill ()
{
    auto needed (size () - buffer.size ());
    auto & lexer_l (lexer);
    for (size_t i (0); i < needed; ++i)
    {
        auto token (lexer_l.lex ());
        if (token.error != nullptr)
        {
            buffer.push_back (new mu::io::end (mu::core::region (lexer.position, lexer.position)));
        }
        else
        {
            buffer.push_back (token.token);
        }
    }
}