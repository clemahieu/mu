#pragma once

#include <vector>

#include <boost/shared_ptr.hpp>

namespace lambda_p_script
{
	class node;
	class reference
	{
	public:
		virtual void operator () (std::vector <boost::shared_ptr <lambda_p_script::node>> & destination) = 0;
	};
}

