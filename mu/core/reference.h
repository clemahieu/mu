#pragma once

#include <mu/core/node.h>

#include <boost/shared_ptr.hpp>

namespace mu
{
	namespace core
	{
		class expression;
		class reference : public mu::core::node
		{
		public:
			reference ();
			reference (mu::core::expression * expression_a, size_t index_a);
			void operator () (mu::core::visitor * visitor_a) override;
			mu::core::expression * expression;
			size_t index;
		};
	}
}
