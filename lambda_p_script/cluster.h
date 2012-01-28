#pragma once

#include <lambda_p/node.h>

#include <vector>
#include <map>

#include <boost/shared_ptr.hpp>

namespace lambda_p_script
{
	class routine;
	class cluster : public lambda_p::node
	{
	public:
		cluster (std::vector <boost::shared_ptr <lambda_p_script::routine>> routines_a);
		cluster (std::map <std::wstring, size_t> names_a, std::vector <boost::shared_ptr <lambda_p_script::routine>> routines_a);
		std::map <std::wstring, size_t> names;
		std::vector <boost::shared_ptr <lambda_p_script::routine>> routines;
	};
}

