#include <mu/io/analyzer/extensions/extensions.h>

mu::io::analyzer::extensions::extensions::extensions ()
{
}

mu::io::analyzer::extensions::extensions::~extensions ()
{
}

mu::io::analyzer::extensions::extensions::extensions (std::map <mu::string, mu::io::analyzer::extensions::extension *, std::less <mu::string>, gc_allocator <std::pair <mu::string, mu::io::analyzer::extensions::extension *>>> extensions_a)
	: extensions_m (extensions_a)
{
}

mu::io::analyzer::extensions::extension * mu::io::analyzer::extensions::extensions::operator () (mu::string const & string)
{
    auto existing (extensions_m.find (string));
    mu::io::analyzer::extensions::extension * result (nullptr);
    if (existing != extensions_m.end ())
    {
        result = existing->second;
    }
    return result;
}

bool mu::io::analyzer::extensions::extensions::operator () (mu::string const & string, mu::io::analyzer::extensions::extension * extension)
{
    auto existing (extensions_m.find (string));
    bool result (existing != extensions_m.end ());
    if (!result)
    {
        extensions_m [string] = extension;
    }
    return result;
}