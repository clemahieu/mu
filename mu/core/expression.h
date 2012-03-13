#pragma once

#include <mu/core/node.h>
#include <mu/core/context.h>

#include <vector>

#include <boost/shared_ptr.hpp>

namespace mu
{
	namespace core
	{
		class expression : public mu::core::node
		{
		public:
			std::vector <boost::shared_ptr <mu::core::node>> dependencies;
			void operator () (mu::core::visitor * visitor_a) override;
		};
	}
}

