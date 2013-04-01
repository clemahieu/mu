#include <mu/core/error_string.hpp>

mu::core::error_string::error_string (char32_t const * message_a, mu::core::error_type type_a):
type_m (type_a),
message (message_a)
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