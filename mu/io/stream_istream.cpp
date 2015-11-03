#include <mu/io/stream_istream.hpp>

#include <assert.h>

mu::io::stream_istream::stream_istream (std::istream & stream_a, size_t size_a):
buffer (size_a),
stream (stream_a)
{
	refill ();
}

void mu::io::stream_istream::consume (size_t size_a)
{
	assert (size_a <= size ());
	buffer.erase (buffer.begin (), buffer.begin () + size_a);
	refill ();
}

char32_t & mu::io::stream_istream::operator [] (size_t size_a)
{
	assert (size_a <= size ());
	auto & result (buffer [size_a]);
	return result;
}

size_t mu::io::stream_istream::size ()
{
	auto result (buffer.size ());
	return result;
}

void mu::io::stream_istream::refill ()
{
	auto needed (size () - buffer.size ());
	auto & stream_l (stream);
	for (size_t i (0); i < needed; ++i)
	{
		auto character (stream_l.get ());
		if (stream_l.eof () || stream_l.fail ())
		{
			buffer.push_back (U'\U0000FFFF');
		}
		else
		{
			buffer.push_back (character);
		}
	}
}
