#pragma once

#include <string>
#include <vector>
#include <map>
#include <set>

#include <boost/circular_buffer.hpp>

#include <gc_allocator.h>

namespace mu
{
    typedef std::basic_string <char32_t> string;
    template <typename T>
    using vector = std::vector <T, gc_allocator <T>>;
    template <typename T>
    using circular_buffer = boost::circular_buffer <T, gc_allocator <T>>;
    template <typename T, typename U>
    using map = std::map <T, U, std::less <T>, gc_allocator <std::pair <T, U>>>;
    template <typename T, typename U>
    using multimap = std::multimap <T, U, std::less <T>, gc_allocator <std::pair <T, U>>>;
    template <typename T>
    using set = std::set <T, std::less <T>, gc_allocator <T>>;
    template <typename T, typename U>
}