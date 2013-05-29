#include <mu/core/string_hash.hpp>

#include <mu/core/MurmurHash3.h>

mu::core::string_hash::string_hash (mu::string const & string_a)
{
    MurmurHash3_x86_128 (string_a.c_str (), string_a.size () * sizeof (mu::string::value_type), 0, &hash);
}

mu::core::string_hash::string_hash (std::string const & string_a)
{
    MurmurHash3_x86_128 (string_a.c_str (), string_a.size (), 0, &hash);
}

mu::string mu::core::string_hash::text ()
{
    mu::string result;
    for (auto i: hash)
    {
        char buffer [2];
        sprintf (buffer, "%02x", i);
        result.push_back (buffer [0]);
        result.push_back (buffer [1]);
    }
    return result;
}