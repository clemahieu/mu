#pragma once

#include <mu/core/node.h>

#include <vector>
#include <map>

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
                locals (size_t parameters_a);
                size_t parameters;
				std::map <mu::script::runtime::expression *, boost::tuple <size_t, size_t>> expressions;
				std::vector <mu::core::node *> frame;
			};
		}
	}
}