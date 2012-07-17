#include <mu/io/analyzer/extensions/extensions.h>

#include <mu/io/analyzer/extensions/extension.h>
#include <boost/algorithm/string.hpp>

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
    auto existing (extensions_m.lower_bound (string));
    bool result (false);
    if ((*extension) ())
    {
        if (existing != extensions_m.end ())
        {
            result = boost::starts_with (existing->first, string);
        }
    }
    if (existing != extensions_m.begin ())
    {
        --existing;
        if ((*existing->second) ())
        {
            result = boost::starts_with (string, existing->first);
        }
    }
    if (!result)
    {
        extensions_m [string] = extension;
    }
    return result;
}