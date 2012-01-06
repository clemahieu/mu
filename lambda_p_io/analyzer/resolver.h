#pragma once

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	class call;
}
namespace lambda_p_io
{
	namespace analyzer
	{
		class unresolved;
		class resolver
		{
		public:
			resolver (boost::shared_ptr <lambda_p_io::analyzer::unresolved> unresolved_a, boost::shared_ptr <lambda_p::call> call_a);
			boost::shared_ptr <lambda_p_io::analyzer::unresolved> unresolved;
			boost::shared_ptr <lambda_p::call> call;
			size_t index;
		};
	}
}

