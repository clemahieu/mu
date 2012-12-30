#pragma once

#include <string>
#include <vector>

#include <boost/circular_buffer.hpp>

#include <gc_allocator.h>

namespace mu
{
    typedef std::basic_istream <char32_t> istream;
    typedef std::basic_string <char32_t> string;
    typedef std::basic_stringstream <char32_t> stringstream;
    template <typename T>
    using vector = std::vector <T, gc_allocator <T>>;
    template <typename T>
    using circular_buffer = boost::circular_buffer <T, gc_allocator <T>>;
}