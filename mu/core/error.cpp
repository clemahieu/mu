#include <mu/core/error.hpp>

#include <sstream>

mu::core::error::~error ()
{
}

std::string mu::core::error::string ()
{
    std::stringstream buffer;
    output (buffer);
    return buffer.str ();
}