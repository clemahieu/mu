#pragma once

#include <string>
#include <vector>
#include <map>
#include <set>
#include <stack>
#include <unordered_map>

#include <boost/circular_buffer.hpp>
#include <boost/cast.hpp>
#include <boost/format.hpp>

#include <gc_allocator.h>

namespace mu
{
    using string = std::basic_string <char32_t>;
	using format = boost::basic_format <char32_t>;
    template <typename T>
    using vector = std::vector <T, gc_allocator <T>>;
    template <typename T>
    using circular_buffer = boost::circular_buffer <T, gc_allocator <T>>;
    template <typename T, typename U>
    using map = std::map <T, U, std::less <T>, gc_allocator <std::pair <T, U>>>;
	template <typename T, typename U>
	using unordered_map = std::unordered_map <T, U, std::hash <T>, std::equal_to <T>, gc_allocator <std::pair <T const, U>>>;
    template <typename T, typename U>
    using multimap = std::multimap <T, U, std::less <T>, gc_allocator <std::pair <T, U>>>;
    template <typename T>
    using set = std::set <T, std::less <T>, gc_allocator <T>>;
	template <typename T, typename U>
	T * cast (U * x)
	{
		auto result (boost::polymorphic_downcast <T *> (x));
		return result;
	}
    std::string std_from_mu_string (mu::string const & string_a);
}