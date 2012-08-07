#include <mu/script/check.h>

#include <mu/core/errors/error_target.h>
#include <mu/core/node.h>

void mu::script::size_fail (mu::core::errors::error_target & errors_a, size_t expected, size_t actual)
{
    mu::stringstream message;
    message << U"Unexpected number of arguments, have: ";
    message << expected;
    message << U" expecting: ";
    message << actual;
    errors_a (message.str ());
}

void mu::script::type_fail (mu::core::errors::error_target & errors_a, std::type_info const & expected, mu::core::node * actual, size_t position)
{
    mu::stringstream message;
    message << U"Unexpected type at position: ";
    message << position;
    message << U", expecting: ";
    message << expected.name ();
    message << U", have: ";
    message << typeid (*actual).name ();
    errors_a (message.str ());
}