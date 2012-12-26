#include <mu/io/stream_muistream.hpp>

#include <assert.h>

mu::io::stream_muistream::stream_muistream (mu::istream & stream_a, size_t size_a):
buffer (size_a),
stream (stream_a)
{
    refill ();
}

void mu::io::stream_muistream::consume (size_t size_a)
{
    assert (size_a <= size ());
    buffer.erase_begin (size_a);
    refill ();
}

char32_t & mu::io::stream_muistream::operator [] (size_t size_a)
{
    assert (size_a <= size ());
    auto & result (buffer [size_a]);
    return result;
}
size_t mu::io::stream_muistream::size ()
{
    auto result (buffer.capacity ());
    return result;
}

void mu::io::stream_muistream::refill ()
{
    auto needed (size () - buffer.size ());
    auto & stream_l (stream);
    for (size_t i (0); i < needed; ++i)
    {
        auto character (stream_l.get ());
        if (stream_l.eof ())
        {
            buffer.push_back (eos_char);
        }
        else
        {
            buffer.push_back (character);
        }
    }
}