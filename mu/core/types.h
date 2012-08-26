#pragma once

#include <string>
#include <sstream>
#include <vector>
#include <set>
#include <map>
#include <deque>
#include <stack>

#include <gc_allocator.h>

namespace mu
{
    typedef std::basic_string <char32_t> string;
    typedef std::basic_stringstream <char32_t> stringstream;
    typedef std::basic_ostream <char32_t> ostream;
    typedef std::basic_istream <char32_t> istream;
    template <typename T>
    using vector = std::vector <T, gc_allocator<T>>;
    template <typename T>
    using set = std::set <T, std::less <T>, gc_allocator <T>>;
    template <typename T, typename U>
    using map = std::map <T, U, std::less <T>, gc_allocator<std::pair <T, U>>>;
    template <typename T>
    using stack = std::stack <T, std::deque <T, gc_allocator <T>>>;
    template <typename T, typename U>
    using multimap = std::multimap <T, U, std::less <T>, gc_allocator<std::pair <T, U>>>;
}