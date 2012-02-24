#pragma once

#include <core/node.h>

#include <map>

#include <boost/shared_ptr.hpp>

namespace lambda_p_script
{
	namespace package
	{
		class node : public mu::core::node
		{
		public:
			std::map <std::wstring, boost::shared_ptr <mu::core::node>> items;
			std::wstring debug () override;
		};
	}
}

