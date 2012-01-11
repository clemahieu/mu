#pragma once

#include <vector>

namespace lambda_p_script
{
	template <typename T>
	class segment
	{
	public:
		segment (size_t lower_a, size_t upper_a, std::vector <T> & source_a)
			: lower (lower_a),
			upper (upper_a),
			source (source_a)
		{
		}
		T & operator [] (size_t position_a)
		{
			return source [lower + position_a];
		}
		typename std::vector <T>::iterator begin ()
		{
			return source.begin () + lower;
		}
		typename std::vector <T>::iterator end ()
		{
			return source.begin () + upper + 1;
		}
		size_t lower;
		size_t upper;
		std::vector <T> & source;
	};
}

