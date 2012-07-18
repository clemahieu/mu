#include <mu/io/lexer/wistream_input.h>

#include <vector>

mu::io::lexer::wistream_input::wistream_input (std::wistream & source_a)
	: source (source_a)
{
}

char32_t mu::io::lexer::wistream_input::operator () ()
{
	wchar_t result (source.get ());
	if (source.eof ())
	{
		result = L'\uffff';
	}
	return result;
}

bool mu::io::lexer::wistream_input::operator () (size_t first, size_t last, mu::string & target)
{
    bool result (false);
    auto original (source.tellg ());
    source.seekg (first, std::ios_base::beg);
    std::vector <wchar_t> data (last - first + 1);
    source.read (data.data (), last - first + 1);
    source.seekg (original);
    target.assign (data.begin (), data.end ());
    return result;
}