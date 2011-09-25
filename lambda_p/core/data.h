#pragma once

#include <string>

#include <lambda_p/core/node.h>

#include <boost/cstdint.hpp>
#include <boost/shared_array.hpp>

namespace lambda_p
{
	namespace core
	{
		class routine;
		class data : public node
		{
		public:
			data (::std::wstring string_a);
			~data (void);
            ::std::wstring string () const;
			node_id node_type () const;
			::std::wstring node_type_name () const;
		private:
			::std::wstring string_m;
		};
	}
}

