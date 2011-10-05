#pragma once

#include <string>

#include <lambda_p/core/node.h>

#include <boost/cstdint.hpp>
#include <boost/shared_array.hpp>

namespace lambda_p
{
	namespace binder
	{
		class data : public ::lambda_p::core::node
		{
		public:
			data (::std::wstring string_a);
			~data (void);
            ::std::wstring string () const;
			::lambda_p::core::node_id node_type () const;
		private:
			::std::wstring string_m;
		};
	}
}

