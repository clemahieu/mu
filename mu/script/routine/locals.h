#pragma once

#include <mu/core/node.h>

#include <map>
#include <vector>

#include <boost/shared_ptr.hpp>
#include <boost/tuple/tuple.hpp>

namespace mu
{
	namespace core
	{
		class expression;
	}
	namespace script
	{
		namespace routine
		{
			class locals : public mu::core::node
			{
			public:
				std::map <boost::shared_ptr <mu::core::expression>, boost::tuple <size_t, size_t>> ranges;
				std::vector <boost::shared_ptr <mu::core::node>> frame;
			};
		}
	}
}