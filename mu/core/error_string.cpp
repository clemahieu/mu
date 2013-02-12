#include <mu/core/error_string.hpp>

mu::core::error_string::error_string (char32_t const * message_a):
message (message_a)
{
}

void mu::core::error_string::output (std::ostream & out)
{
    std::string string (message.begin (), message.end ());
    out << string;
}