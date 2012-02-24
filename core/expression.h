#pragma once

#include <core/node.h>
#include <core/context.h>

#include <vector>

#include <boost/shared_ptr.hpp>

namespace mu
{
	namespace core
	{
		class expression : public mu::core::node
		{
		public:
			expression (mu::core::context context_a);
			mu::core::context context;
			std::vector <boost::shared_ptr <mu::core::node>> dependencies;
			void operator () (mu::core::visitor * visitor_a) override;
		};
	}
}

