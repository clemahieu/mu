#pragma once

#include <vector>

namespace mu
{
	namespace core
	{
		template <typename T, typename U = std::vector <T>>
		class segment
		{
		public:
			segment (U & source_a)
				: lower (0),
				source (source_a)
			{
			}
			segment (size_t lower_a, U & source_a)
				: lower (lower_a),
				source (source_a)
			{
			}
			T & operator [] (size_t position_a)
			{
				return source [lower + position_a];
			}
			typename U::iterator begin ()
			{
				return source.begin () + lower;
			}
			typename U::iterator end ()
			{
				return source.end ();
			}
			void resize (size_t size_a)
			{
				source.resize (size_a + lower);
			}
			size_t size ()
			{
				return source.size () - lower;
			}
			size_t lower;
			U & source;
		};
	}
}
