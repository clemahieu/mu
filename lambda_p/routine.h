#pragma once

#include <lambda_p/node.h>

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	class set;
	class routine : public lambda_p::node
	{
	public:
		routine ();
		boost::shared_ptr <lambda_p::set> parameters;
		boost::shared_ptr <lambda_p::set> body;
	};
}

