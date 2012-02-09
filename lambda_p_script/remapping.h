#pragma once

#include <map>

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	class routine;
}
namespace lambda_p_script
{
	class routine;
	class remapping
	{
	public:
		std::map <boost::shared_ptr <lambda_p::routine>, boost::shared_ptr <lambda_p_script::routine>> generated;
	};
}

