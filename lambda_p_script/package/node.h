#pragma once

#include <lambda_p/node.h>

#include <map>

#include <boost/shared_ptr.hpp>

namespace lambda_p_script
{
	namespace package
	{
		class node : public lambda_p::node
		{
		public:
			std::map <std::wstring, boost::shared_ptr <lambda_p::node>> items;
		};
	}
}

