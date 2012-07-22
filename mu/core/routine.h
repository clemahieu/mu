#pragma once

#include <mu/io/debugging/context.h>
#include <mu/core/node.h>

namespace mu
{
	namespace core
	{
		class expression;
		class routine : public mu::core::node
		{
		public:
			routine ();
			routine (mu::core::expression * body_a);
			void operator () (mu::core::visitor * visitor_a) override;
            mu::string name () override;
			mu::core::expression * body;
		};
	}
}
