#include <mu/io/lexer_istream_input.h>

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
		result = U'\uffff';
	}
	return result;
}

bool mu::io::lexer::istream_input::operator () (size_t const first, size_t const size, mu::string & target)
{
    auto original (source.tellg ());
    source.seekg (first, std::ios_base::beg);
    std::vector <char> data (size);
    source.read (data.data (), size);
    bool result (source.fail () || source.eof ());
    source.seekg (original);
    target.assign (data.begin (), data.end ());
    return result;
}