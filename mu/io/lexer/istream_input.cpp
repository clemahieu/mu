#include <mu/io/lexer/istream_input.h>

#include <vector>

mu::io::lexer::istream_input::istream_input (std::istream & source_a)
	: source (source_a)
{
}

char32_t mu::io::lexer::istream_input::operator() ()
{
	wchar_t result (source.get ());
	if (source.eof ())
	{
		result = L'\uffff';
	}
	return result;
}

bool mu::io::lexer::istream_input::operator () (size_t const first, size_t const last, mu::string & target)
{
    bool result (false);
    auto original (source.tellg ());
    source.seekg (first, std::ios_base::beg);
    std::vector <char> data (last - first + 1);
    source.read (data.data (), last - first + 1);
    source.seekg (original);
    target.assign (data.begin (), data.end ());
    return result;
}