#pragma once

#include <boost/shared_ptr.hpp>

#include <vector>

namespace lambda_p_script
{
	class node;
	class context
	{
	public:
		std::vector <boost::shared_ptr <lambda_p_script::node>> values;
	};
}

