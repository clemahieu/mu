#pragma once

#include <lambda_p/node.h>

#include <map>
#include <string>

#include <boost/shared_ptr.hpp>

namespace lambda_p
{
	class routine;
	class cluster : public lambda_p::node
	{
	public:
		std::map <std::wstring, boost::shared_ptr <lambda_p::routine>> routines;
	};
}

