#pragma once

#include <mu/core/segment.h>

#include <boost/shared_ptr.hpp>

namespace mu
{
	namespace core
	{
		class node;
		namespace apply
		{
			void merge (std::vector <boost::shared_ptr <mu::core::node>> & target, std::vector <boost::shared_ptr <mu::core::node>> & source);
		}
	}
}
