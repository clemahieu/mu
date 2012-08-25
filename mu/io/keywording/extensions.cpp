#include <mu/io/keywording/extensions.h>

#include <boost/algorithm/string.hpp>
#include <mu/io/keywording/global.h>

#include <gc_cpp.h>

mu::io::keywording::extensions::extensions ()
{
}

mu::io::keywording::extensions::extensions (mu::map <mu::string, extension_definition> extensions_a)
	: extensions_m (extensions_a)
{
}

boost::tuple <mu::io::keywording::extension_factory, mu::string> mu::io::keywording::extensions::operator () (mu::string const & string)
{
    boost::tuple <mu::io::keywording::extension_factory, mu::string> result;
    if (!extensions_m.empty ())
    {
        auto existing (extensions_m.upper_bound (string));
        if (existing != extensions_m.begin ())
        {
            --existing;
            if (boost::get <1> (existing->second) && boost::starts_with (string, existing->first))
            {
                boost::get <0> (result) = boost::get <0> (existing->second);
                boost::get <1> (result) = string;
            }
            else if (string == existing->first)
            {
                boost::get <0> (result) = boost::get <0> (existing->second);
                boost::get <1> (result) = string;
            }
        }
    }
    return result;
}

bool mu::io::keywording::extensions::operator () (mu::string const & string, mu::io::keywording::extension_factory extension, bool dominating_a)
{
    auto existing (extensions_m.lower_bound (string));
    bool result (false);
    if (dominating_a)
    {
        if (existing != extensions_m.end ())
        {
            result = boost::starts_with (existing->first, string);
        }
    }
    if (existing != extensions_m.begin ())
    {
        --existing;
        if (boost::get <1> (existing->second))
        {
            result = boost::starts_with (string, existing->first);
        }
    }
    if (!result)
    {
        extensions_m [string] = mu::io::keywording::extension_definition (extension, dominating_a);
    }
    return result;
}

bool mu::io::keywording::extensions::operator () (mu::string const & string, mu::core::node * node_a)
{
    auto result ((*this) (string, [node_a]
                          (mu::io::keywording::keywording & keywording_a)
                          {
                              return new (GC) mu::io::keywording::global (keywording_a, node_a);
                          }, false));
    return result;
}