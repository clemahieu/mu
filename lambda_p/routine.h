#pragma once

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	class node;
	class set;
	class routine
	{
	public:
		routine ();
		boost::shared_ptr <lambda_p::node> parameters;
		boost::shared_ptr <lambda_p::set> body;
	};
}

