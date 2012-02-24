#pragma once

#include <core/node.h>

namespace mu
{
	namespace core
	{
		class parameters : public mu::core::node
		{
		public:
			void operator () (mu::core::visitor * visitor_a) override;
		};
	}
}
