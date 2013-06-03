#include <mu/core/error_string.hpp>

mu::core::error_string::error_string (char32_t const * message_a, mu::core::error_type type_a, mu::core::region const & region_a):
type_m (type_a),
message (message_a),
region_m (region_a)
{
}

mu::core::error_type mu::core::error_string::type ()
{
    return type_m;
}

void mu::core::error_string::output (std::ostream & out)
{
    std::string string (message.begin (), message.end ());
    mu::string const & region_mu (region_m.string ());
    std::string region (region_mu.begin (), region_mu.end ());
    out << string << "(" << region << ")";
}

mu::core::region mu::core::error_string::region ()
{
	return region_m;
}