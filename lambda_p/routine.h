#pragma once

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	class call;
	class parameters;
	class routine
	{
	public:
		routine ();
		boost::shared_ptr <lambda_p::parameters> parameters;
		boost::shared_ptr <lambda_p::call> call;
	};
}

