#include <mu/io/lexer_wistream_input.h>

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

bool mu::io::lexer::wistream_input::operator () (size_t first, size_t size, mu::string & target)
{
    auto original (source.tellg ());
    source.seekg (first, std::ios_base::beg);
    std::vector <wchar_t> data (size);
    source.read (data.data (), size);
    bool result (source.fail () || source.eof ());
    source.seekg (original);
    target.assign (data.begin (), data.end ());
    return result;
}