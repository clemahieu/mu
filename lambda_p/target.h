#pragma once

#include <vector>

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	class node;
	class target
	{
	public:
		virtual void operator () (std::vector <boost::shared_ptr <lambda_p::node>> & arguments) = 0;
	};
}

