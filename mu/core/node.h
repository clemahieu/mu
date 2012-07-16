#pragma once

#include <mu/core/types.h>

namespace mu
{
	namespace core
	{
		class visitor;
		class node
		{
		public:
			virtual ~node ();
			virtual void operator () (mu::core::visitor * visitor_a);
			virtual mu::string name ();
			virtual mu::string debug ();
		};
	}
}