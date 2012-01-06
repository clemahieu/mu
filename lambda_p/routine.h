#pragma once

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	class call;
	class routine
	{
	public:
		routine (boost::shared_ptr <lambda_p::call> call_a);
		boost::shared_ptr <lambda_p::call> call;
	};
}

