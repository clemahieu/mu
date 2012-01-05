#pragma once

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	class expression;
}
namespace lambda_p_io
{
	namespace analyzer
	{
		class resolver
		{
		public:
			boost::shared_ptr <lambda_p::expression> expression;
			size_t index;
			bool complete;
		};
	}
}

