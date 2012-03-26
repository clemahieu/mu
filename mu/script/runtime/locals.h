#pragma once

#include <mu/core/node.h>

#include <vector>
#include <map>

#include <boost/shared_ptr.hpp>
#include <boost/tuple/tuple.hpp>

namespace mu
{
	namespace script
	{
		namespace runtime
		{
			class expression;
			class locals : public mu::core::node
			{
			public:
				std::map <boost::shared_ptr <mu::script::runtime::expression>, boost::tuple <size_t, size_t>> expressions;
				std::vector <boost::shared_ptr <mu::core::node>> frame;
			};
		}
	}
}