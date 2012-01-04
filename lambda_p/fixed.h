#pragma once

#include <boost/shared_ptr.hpp>

#include <vector>

namespace lambda_p
{
	class tee;
	class node;
	class fixed
	{
	public:
		fixed ();
		void operator () ();
		boost::shared_ptr <lambda_p::tee> target;
		std::vector <boost::shared_ptr <lambda_p::node>> arguments;
	};
}

