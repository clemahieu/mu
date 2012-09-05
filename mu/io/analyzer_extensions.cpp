#include <mu/io/analyzer_extensions.h>

#include <boost/algorithm/string.hpp>
#include <mu/io/analyzer_global.h>

#include <gc_cpp.h>

mu::io::analyzer::extensions::extensions ()
{
}

mu::io::analyzer::extensions::extensions (mu::map <mu::string, extension_definition> extensions_a)
	: extensions_m (extensions_a)
{
}

boost::tuple <mu::io::analyzer::extension_factory, mu::string> mu::io::analyzer::extensions::operator () (mu::string const & string)
{
    boost::tuple <mu::io::analyzer::extension_factory, mu::string> result;
    if (!extensions_m.empty ())
    {
        auto existing (extensions_m.upper_bound (string));
        if (existing != extensions_m.begin ())
        {
            --existing;
            if (boost::get <1> (existing->second) && boost::starts_with (string, existing->first))
            {
                boost::get <0> (result) = boost::get <0> (existing->second);
                boost::get <1> (result) = existing->first;
            }
            else if (string == existing->first)
            {
                boost::get <0> (result) = boost::get <0> (existing->second);
                boost::get <1> (result) = existing->first;
            }
        }
    }
    return result;
}

bool mu::io::analyzer::extensions::operator () (mu::string const & string, mu::io::analyzer::extension_factory extension, bool dominating_a)
{
    auto existing (extensions_m.lower_bound (string));
    bool result (false);
    if (dominating_a)
    {
        if (existing != extensions_m.end ())
        {
            result = result | boost::starts_with (existing->first, string);
        }
    }
    if (existing != extensions_m.begin ())
    {
        --existing;
        if (boost::get <1> (existing->second))
        {
            result = result | boost::starts_with (string, existing->first);
        }
    }
    else if (existing != extensions_m.end ())
    {
        result = result | (string == existing->first);
    }
    if (!result)
    {
        extensions_m [string] = mu::io::analyzer::extension_definition (extension, dominating_a);
    }
    return result;
}

bool mu::io::analyzer::extensions::operator () (mu::string const & string, mu::core::node * node_a)
{
    auto result ((*this) (string, [node_a]
                          (mu::io::analyzer::analyzer & analyzer_a)
                          {
                              return new (GC) mu::io::analyzer::global (analyzer_a, node_a);
                          }, false));
    return result;
}