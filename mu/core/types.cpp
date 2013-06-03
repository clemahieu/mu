#include <mu/core/types.hpp>

std::string std_from_mu_string (mu::string const & string_a)
{
    std::string result (string_a.begin (), string_a.end ());
    return result;
}