#pragma once

#include <string>
#include <vector>
#include <map>
#include <set>
#include <stack>
#include <unordered_map>

namespace mu
{
	using string = std::basic_string <char32_t>;
	template <typename T>
	using vector = std::vector <T>;
	template <typename T, typename U>
	using map = std::map <T, U>;
	template <typename T, typename U>
	using unordered_map = std::unordered_map <T, U>;
	template <typename T, typename U>
	using multimap = std::multimap <T, U>;
	template <typename T, typename U>
	using unordered_multimap = std::unordered_multimap <T, U>;
	template <typename T>
	using set = std::set <T>;
	template <typename T, typename U>
	T * cast (U * x)
	{
		auto result (dynamic_cast <T *> (x));
		assert (result != nullptr);
		return result;
	}
	std::string std_from_mu_string (mu::string const & string_a);
}
