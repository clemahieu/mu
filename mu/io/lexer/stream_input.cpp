#include <mu/io/lexer/stream_input.h>

#include <vector>

mu::io::lexer::stream_input::stream_input (mu::istream & source_a)
: source (source_a)
{
}

char32_t mu::io::lexer::stream_input::operator () ()
{
	wchar_t result (source.get ());
	if (source.eof ())
	{
		result = U'\U0000FFFF';
	}
	return result;
}

bool mu::io::lexer::stream_input::operator () (size_t const first, size_t const last, mu::string & target)
{
    bool result (false);
    auto original (source.tellg ());
    source.seekg (first, std::ios_base::beg);
    std::vector <char32_t> data (last - first + 1);
    source.read (data.data (), last - first + 1);
    source.seekg (original);
    target.assign (data.begin (), data.end ());
    return result;
}