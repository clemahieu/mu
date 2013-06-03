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
    out << string;
}

mu::core::region mu::core::error_string::region ()
{
	return region_m;
}