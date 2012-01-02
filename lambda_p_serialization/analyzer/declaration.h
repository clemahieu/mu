#pragma once

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	namespace core
	{
		class target;
	}
}
namespace lambda_p_serialization
{
	namespace analyzer
	{
		class declaration
		{
		public:
			virtual void operator () (boost::shared_ptr <lambda_p::core::target> target_a) = 0;
		};
	}
}

